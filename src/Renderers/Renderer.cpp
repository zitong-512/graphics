#include "Renderers/Renderer.hpp"

#include <algorithm>
#include <cmath>
#include <vector>

namespace {
    Material materialAt(const Hit& hit) {
        const Material& material = hit.object->material();
        return material.materialTexture
            ? material.materialTexture->sample(hit.uv)
            : material;
    }
}

float Renderer::shadow(const Scene& scene, const Hit& hit, const PointLight& light) const {
    const Vec3 toLight = light.position() - hit.point;
    const float lightDistance = length(toLight);

    if (lightDistance <= shadowBias_) { return 1.0f; }

    const Ray shadowRay{hit.point + hit.normal * shadowBias_, toLight / lightDistance};
    const std::optional<Hit> entryHit = closestHit(scene, shadowRay, lightDistance);
    if (!entryHit || entryHit->object == nullptr) { return 1.0f; }

    // Start just inside the blocker and continue toward the light.
    const Ray exitRay{
        entryHit->point - shadowBias_ * entryHit->normal,
        shadowRay.direction
    };
    const std::optional<float> exit =
        exitDistance(*entryHit->object, exitRay, lightDistance - entryHit->t);
    if (!exit) { return 0.0f; }

    constexpr float shadowDensity = 10.0f;
    return std::exp(-shadowDensity * *exit);
}

std::vector<LightPtr> Renderer::visibleLights(const Scene& scene, const Hit& hit) const {
    std::vector<LightPtr> visibleLights;
    visibleLights.reserve(scene.lights().size());

    for (const LightPtr& light : scene.lights()) {
        if (!light) { continue; }

        const auto* pointLight = dynamic_cast<const PointLight*>(light.get());
        if (pointLight == nullptr) {
            visibleLights.push_back(light);
            continue;
        }

        // Important bit
        const float visibility = shadow(scene, hit, *pointLight);
        visibleLights.push_back(std::make_shared<PointLight>(
            pointLight->position(), visibility * pointLight->color()));
    }

    return visibleLights;
}

/* Final color */

Vec3 Renderer::color(const Scene& scene, const Ray& ray, int depth) const {
    const std::optional<Hit> hit = closestHit(scene, ray, maxDistance_);
    if (!hit || hit->object == nullptr) { return scene.background(); }

    const Vec3 surfaceColor = localColor(scene, *hit);
    const Material material = materialAt(*hit);
    const float reflectiveness = std::clamp(material.reflectiveness, 0.0f, 1.0f);
    const float transmission =
        std::clamp(material.transmissivity, 0.0f, 1.0f - reflectiveness);
    const float surfaceWeight = 1.0f - reflectiveness - transmission;

    Vec3 color = surfaceWeight * surfaceColor;
    if (reflectiveness > 0.0f) {
       color = color + reflectionColor(scene, ray, *hit, depth - 1);
    }
    if (transmission > 0.0f) {
        color = color + refractionColor(scene, ray, *hit);
    }

    return color;
}

/* Local color */

Vec3 Renderer::localColor(const Scene& scene, const Hit& hit) const {
    const Material material = materialAt(hit);
    return hit.object->shader().shade(
        hit, material, scene.camera(), visibleLights(scene, hit));
}

/* Reflections */
// To add depth, add it to `reflectionColor` and `color`

Ray Renderer::reflectedRay(const Ray& incomingRay, const Hit& hit) const {
    // Important to use an offset (:
    Vec3 l = normalize(incomingRay.direction);
    Vec3 n = normalize(hit.normal);
    Vec3 r = normalize(l - ((2 * dot(l, n)) * n));
    const Vec3 offsetNormal = dot(r, n) >= 0.0f ? n : -n;
    return {hit.point + shadowBias_ * offsetNormal, r};
}

Vec3 Renderer::reflectionColor(
    const Scene& scene, const Ray& incomingRay, const Hit& hit, int depth) const {
    const Ray& reflected = reflectedRay(incomingRay, hit);
    const std::optional<Hit> reflectedHit = closestHit(
        scene, reflectedRay(incomingRay, hit), maxDistance_);
    if (!reflectedHit || reflectedHit->object == nullptr) {return scene.background(); }

    return color(scene, reflected, depth - 1);
}


/* Refraction*/

std::optional<Ray> Renderer::refractedRay(const Ray& incomingRay, const Hit& hit,
    float sourceRefractiveIndex, float destinationRefractiveIndex) const {
    if (sourceRefractiveIndex <= 0.0f || destinationRefractiveIndex <= 0.0f) {
        return std::nullopt;
    }

    const Vec3 incident = normalize(incomingRay.direction);
    Vec3 normal = normalize(hit.normal);
    if (dot(incident, normal) >= 0.0f) { normal = -normal; }

    const float cos1 = std::clamp(-dot(incident, normal), 0.0f, 1.0f);
    const float sin1 = std::sqrt(std::max(0.0f, 1.0f - cos1 * cos1));

    const float indexRatio = sourceRefractiveIndex / destinationRefractiveIndex;

    const float sin2 = indexRatio * sin1;
    if (sin2 > 1.0f) { return std::nullopt; }
    const float cos2 = std::sqrt(std::max(0.0f, 1.0f - sin2 * sin2));

    const Vec3 direction =
        normalize(indexRatio * incident + (indexRatio * cos1 - cos2) * normal);

    return Ray{hit.point - shadowBias_ * normal, direction};
}

Vec3 Renderer::refractionColor(
    const Scene& scene, const Ray& incomingRay, const Hit& hit) const {
    [[maybe_unused]] constexpr float airRefractiveIndex = 1.0f;
    [[maybe_unused]] const float objectRefractiveIndex =
        materialAt(hit).refractiveIndex;

    const std::optional<Ray> entryRay = refractedRay(incomingRay, hit, airRefractiveIndex, objectRefractiveIndex);
    if (!entryRay) { return scene.background(); }
    const std::optional<float> exit = exitDistance(*hit.object, *entryRay, maxDistance_);
    if (!exit) { return scene.background(); }

    const Vec3 exitPoint = entryRay->at(*exit);
    const Hit exitHit{
        *exit,
        exitPoint,
        hit.object->transformedNormal(exitPoint),
        hit.object->transformedTextureCoordinates(exitPoint),
        hit.object
    };

    /*
     TODO 
     Use `materialAt` to get the material at the exit point
     and if it is not transmissive, shade the inside of the object.
    */ 
    Material hitMaterial = materialAt(exitHit);


    const std::optional<Ray> exitRay = refractedRay(*entryRay, exitHit, objectRefractiveIndex, airRefractiveIndex);
    const Hit coloredtHit{
        *exit,
        exitPoint,
        - hit.object->transformedNormal(exitPoint),
        hit.object->transformedTextureCoordinates(exitPoint),
        hit.object
    };

    if (!exitRay) { return scene.background(); }

    const std::optional<Hit> refractedHit = closestHit(scene, *exitRay, maxDistance_);
    if (!refractedHit || refractedHit->object == nullptr) { return scene.background(); }

    return localColor(scene, *refractedHit);
}
