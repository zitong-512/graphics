#pragma once

#include <optional>
#include "Scenes/Scene.hpp"
#include "Utilities/Hit.hpp"
#include "Utilities/Ray.hpp"
#include "Lights/PointLight.hpp"

class Raymarching {
public:
    Raymarching(int maxSteps = 128, float maxDistance = 100.0f,
                float surfaceEpsilon = 0.001f)
        : maxSteps_(maxSteps),
          maxDistance_(maxDistance),
          surfaceEpsilon_(surfaceEpsilon) {}

    std::optional<Hit> raymarch(const Scene& scene, const Ray& ray, float maxDistance) const;
    std::optional<Hit> raymarch(const Scene& scene, const Ray& ray) const;

    bool shadow(const Scene& scene, const Hit& hit, const PointLight& light) const;
    Vec3 color(const Scene& scene, const Ray& ray) const;

private:
    int maxSteps_;
    float maxDistance_;
    float surfaceEpsilon_;
};
