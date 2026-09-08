#include "Renders/Renderer.hpp"

#include <algorithm>
#include <cmath>
#include <vector>

/*
Refraction exercises (complete them in this order):

1. Compute cos1 from the incident direction and the oriented surface normal.
2. Compute sin1 from cos1 using the Pythagorean identity.
3. Apply Snell's law to compute sin2, then keep the total-internal-reflection check.
4. Compute cos2 from sin2. The final direction expression is already provided.
5. In refractionColor, replace the fixed entry ray with a call to refractedRay
   that moves from air into the object.
6. Replace the fixed exit ray with a call to refractedRay that moves from the
   object back into air.
*/

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

Vec3 Renderer::color(const Scene& scene, const Ray& ray) const {
    const std::optional<Hit> hit = closestHit(scene, ray, maxDistance_);
    if (!hit || hit->object == nullptr) { return scene.background(); }

    const Vec3 surfaceColor = localColor(scene, *hit);
    const Material& material = hit->object->material();
    const float reflectiveness = std::clamp(material.reflectiveness, 0.0f, 1.0f);
    const float transmission =
        std::clamp(material.transmissivity, 0.0f, 1.0f - reflectiveness);
    const float surfaceWeight = 1.0f - reflectiveness - transmission;

    Vec3 result = surfaceWeight * surfaceColor;
    if (reflectiveness > 0.0f) {
        // Add reflection color
    }
    if (transmission > 0.0f) {
        // Add refraction color
    }

    return result;
}

/* Local color */

Vec3 Renderer::localColor(const Scene& scene, const Hit& hit) const {
    return hit.object->shader().shade(
        hit, hit.object->material(), scene.camera(), visibleLights(scene, hit));
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
    const Scene& scene, const Ray& incomingRay, const Hit& hit) const {
    const std::optional<Hit> reflectedHit = closestHit(
        scene, reflectedRay(incomingRay, hit), maxDistance_);
    if (!reflectedHit || reflectedHit->object == nullptr) { return scene.background(); }

    return localColor(scene, *reflectedHit);
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

    const float cos1 = 0.5f;
    [[maybe_unused]] const float sin1 = 0.5f;

    const float indexRatio = sourceRefractiveIndex / destinationRefractiveIndex;
    const float sin2 = 0.5f;
    if (sin2 > 1.0f) { return std::nullopt; }

    const float cos2 = 0.5f;
    const Vec3 direction =
        normalize(indexRatio * incident + (indexRatio * cos1 - cos2) * normal);

    return Ray{hit.point - shadowBias_ * normal, direction};
}

Vec3 Renderer::refractionColor(
    const Scene& scene, const Ray& incomingRay, const Hit& hit) const {
    [[maybe_unused]] constexpr float airRefractiveIndex = 1.0f;
    [[maybe_unused]] const float objectRefractiveIndex =
        hit.object->material().refractiveIndex;

    // Exercise 5: replace this fixed straight-through ray.
    const std::optional<Ray> entryRay = Ray{
        hit.point - shadowBias_ * normalize(hit.normal),
        normalize(incomingRay.direction)
    };
    if (!entryRay) { return scene.background(); }

    const std::optional<float> exit = exitDistance(*hit.object, *entryRay, maxDistance_);
    if (!exit) { return scene.background(); }

    const Vec3 exitPoint = entryRay->at(*exit);
    const Hit exitHit{*exit, exitPoint, hit.object->normal(exitPoint),
        hit.object->textureCoordinates(exitPoint), hit.object};
    // Exercise 6: replace this fixed straight-through ray.
    const std::optional<Ray> exitRay = Ray{
        exitPoint + shadowBias_ * normalize(exitHit.normal),
        entryRay->direction
    };
    if (!exitRay) { return scene.background(); }

    const std::optional<Hit> refractedHit = closestHit(scene, *exitRay, maxDistance_);
    if (!refractedHit || refractedHit->object == nullptr) { return scene.background(); }

    return localColor(scene, *refractedHit);
}
