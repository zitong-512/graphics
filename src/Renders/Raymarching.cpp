#include "Renders/Raymarching.hpp"

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
    return raymarch(scene, ray, maxDistance_);
}

bool Raymarching::shadow(const Scene& scene,
                         const Hit& hit,
                         const PointLight& light) const {
    Vec3 toLight = light.position() - hit.point;
        if (length(light.position() - toLight) <= surfaceEpsilon_) {
            return false;
        }

    Ray ShadowRay = {hit.point + hit.normal * (2.0f * surfaceEpsilon_), toLight};

    return raymarch(scene, ShadowRay).has_value();

}

Vec3 Raymarching::color(const Scene& scene, const Ray& ray) const {
    const std::optional<Hit> hit = raymarch(scene, ray);
    if (!hit || hit->object == nullptr) {
        return scene.background();
    }

    std::vector<LightPtr> visibleLights;
    visibleLights.reserve(scene.lights().size());

    for (const LightPtr& light : scene.lights()) {
        if (!light) {
            continue;
        }

        const auto* pointLight = dynamic_cast<const PointLight*>(light.get());
        if (pointLight != nullptr && shadow(scene, *hit, *pointLight)) {
            continue;
        }

        visibleLights.push_back(light);
    }

    return hit->object->shader().shade(
        *hit,
        hit->object->material(),
        scene.camera(),
        visibleLights
    );
}
