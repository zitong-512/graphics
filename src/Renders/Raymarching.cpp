#include "Renders/Raymarching.hpp"

#include <algorithm>

std::optional<Hit> Raymarching::raymarch(const Scene& scene, const Ray& ray, float maxDistance) const {
    float traveled = 0.0f;

    for (int step = 0; step < maxSteps_; ++step) {
        const Vec3 point = ray.at(traveled);
        const auto [distance, object] = scene.sdf(point);

        if (distance <= surfaceEpsilon_) {
            Hit hit;
            hit.t = traveled;
            hit.point = point;
            hit.normal = object->normal(point);
            hit.uv = object->textureCoordinates(point);
            hit.object = object;
            return hit;
        }

        traveled += distance;
        if (traveled > maxDistance) {
            return std::nullopt;
        }
    }
    return std::nullopt;
}

std::optional<Hit> Raymarching::raymarch(const Scene& scene, const Ray& ray) const {
    return raymarch(scene, ray, maxDistance());
}

std::optional<Hit> Raymarching::closestHit(const Scene& scene,
                                           const Ray& ray,
                                           float maxDistance) const {
    return raymarch(scene, ray, maxDistance);
}

std::optional<float> Raymarching::exitDistance(const Object& object,
                                               const Ray& ray,
                                               float maxDistance) const {
    if (object.sdf(ray.origin) >= 0.0f) { return std::nullopt; }

    float traveled = 0.0f;
    for (int step = 0; step < maxSteps_; ++step) {
        const float distance = object.sdf(ray.at(traveled));
        if (distance >= 0.0f) { return traveled; }

        traveled += std::max(-distance, surfaceEpsilon_);
        if (traveled > maxDistance) { return std::nullopt; }
    }

    return std::nullopt;
}
