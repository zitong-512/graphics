#include "Renders/Raymarching.hpp"

Vec3 Raymarching::color(const Scene& scene, const Shader& shader,
                        const Ray& ray) const {
    float traveled = 0.0f;

    for (int step = 0; step < maxSteps_; ++step) {
        const Vec3 point = ray.at(traveled);
        Hit hit = scene.sdf(point);

        if (hit.t <= surfaceEpsilon_) {
            hit.normal = scene.normal(point, *hit.object);
            return shader.shade(hit);
        }

        traveled += hit.t;
        if (traveled > maxDistance_) {
            return scene.background();
        }
    }

    return scene.background();
}
