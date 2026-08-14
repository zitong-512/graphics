#include "Renders/Raymarching.hpp"

Vec3 Raymarching::color(const Scene& scene, const Shader& shader,
                        const Ray& ray) const {
    float traveled = 0.0f;

    for (int step = 0; step < maxSteps_; ++step) {
        const Vec3 point = ray.at(traveled);
        const float distance = scene.sdf(point);

        if (distance <= surfaceEpsilon_) {
            Hit hit;
            hit.t = traveled;
            hit.point = point;
            hit.normal = scene.normal(point);
            return shader.shade(hit);
        }

        traveled += distance;
        if (traveled > maxDistance_) {
            return scene.background();
        }
    }

    return scene.background();
}
