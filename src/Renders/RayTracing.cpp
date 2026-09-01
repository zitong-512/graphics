#include "Renders/RayTracing.hpp"

std::optional<Hit> RayTracing::raytrace(const Scene& scene,
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

std::optional<Hit> RayTracing::raytrace(const Scene& scene,
                                        const Ray& ray) const {
    return raytrace(scene, ray, maxDistance());
}

std::optional<Hit> RayTracing::closestHit(const Scene& scene,
                                          const Ray& ray,
                                          float maxDistance) const {
    return raytrace(scene, ray, maxDistance);
}

std::optional<float> RayTracing::exitDistance(const Object& object,
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
