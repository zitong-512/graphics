#include "Renders/Renderer.hpp"

#include <algorithm>
#include <cmath>
#include <vector>

float Renderer::shadow(const Scene& scene, const Hit& hit, const PointLight& light) const {
    const Vec3 toLight = light.position() - hit.point;
    const float lightDistance = length(toLight);

    if (lightDistance <= shadowBias_) {return 1.0f;}

    const Ray shadowRay{hit.point + hit.normal * shadowBias_, toLight / lightDistance};
    constexpr float shadowDensity = 1.0f;

    const std::optional<Hit> entryHit = closestHit(scene, shadowRay, lightDistance);
    if (!entryHit || entryHit->object == nullptr) { return 1.0f; }
    
    // Account for the shadow bias!
    const Ray exitRay{
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f}
    };
    const std::optional<float> exit = exitDistance(
        *entryHit->object, exitRay, lightDistance - entryHit->t
    );
    if (!exit) { return 0.0f; }

    // Use the std::exp function!
    return 0.0f;
}

Vec3 Renderer::color(const Scene& scene, const Ray& ray) const {
    const std::optional<Hit> hit = closestHit(scene, ray, maxDistance_);
    if (!hit || hit->object == nullptr) { return scene.background(); }

    const Vec3 surfaceColor = localColor(scene, *hit);
    const float reflectiveness = hit->object->material().reflectiveness;

    return (1.0f - reflectiveness) * surfaceColor
         + reflectiveness * reflectionColor(scene, ray, *hit);
}

Vec3 Renderer::localColor(const Scene& scene, const Hit& hit) const {
    return hit.object->shader().shade(
        hit,
        hit.object->material(),
        scene.camera(),
        visibleLights(scene, hit)
    );
}
std::vector<LightPtr> Renderer::visibleLights(const Scene& scene,
                                               const Hit& hit) const {
    std::vector<LightPtr> visibleLights;
    visibleLights.reserve(scene.lights().size());

    for (const LightPtr& light : scene.lights()) {
        if (!light) { continue; }

        const auto* pointLight = dynamic_cast<const PointLight*>(light.get());
        if (pointLight == nullptr) { visibleLights.push_back(light); continue; }

        // Important bit
        const float visibility = shadow(scene, hit, *pointLight);
        visibleLights.push_back(std::make_shared<PointLight>(
            pointLight->position(), visibility * pointLight->color()
        ));
    }

    return visibleLights;
}

/* Reflections */

Ray Renderer::reflectedRay(const Ray& incomingRay, const Hit& hit) const {
    // Important to use an offset (:
    //const Vec3 offsetNormal = dot(reflected, normal) >= 0.0f ? normal : -normal;

    return { {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} };
}

Vec3 Renderer::reflectionColor(const Scene& scene, const Ray& incomingRay, const Hit& hit) const {
    const std::optional<Hit> reflectedHit = closestHit(
        scene, reflectedRay(incomingRay, hit), maxDistance_
    );
    if (true) { return scene.background(); }
    else { return {0.0f, 0.0f, 0.0f}; }
}
