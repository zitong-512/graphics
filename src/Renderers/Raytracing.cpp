#include "Renderers/Raytracing.hpp"

std::optional<Hit> Raytracing::raytrace(const Scene& scene,
                                        const Ray& ray,
                                        float maxDistance) const {
    std::optional<Hit> closest;
    float closestDistance = maxDistance;

    for (const ObjectPtr& object : scene.objects()) {
        if (!object) {
            continue;
        }

        std::optional<Hit> hit = object->hit(
            ray,
            intersectionEpsilon_,
            closestDistance
        );
        if (hit) {
            closestDistance = hit->t;
            closest = std::move(hit);
        }
    }

    return closest;
}

std::optional<Hit> Raytracing::raytrace(const Scene& scene,
                                        const Ray& ray) const {
    return raytrace(scene, ray, maxDistance());
}

std::optional<Hit> Raytracing::closestHit(const Scene& scene,
                                          const Ray& ray,
                                          float maxDistance) const {
    return raytrace(scene, ray, maxDistance);
}

std::optional<float> Raytracing::exitDistance(const Object& object,
                                              const Ray& ray,
                                              float maxDistance) const {
    const std::optional<Hit> exitHit = object.hit(
        ray,
        intersectionEpsilon_,
        maxDistance
    );
    if (!exitHit) { return std::nullopt; }

    return exitHit->t;
}
