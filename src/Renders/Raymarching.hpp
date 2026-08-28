#pragma once

#include "Renders/Renderer.hpp"

class Raymarching final : public Renderer {
public:
    Raymarching(int maxSteps = 128, float maxDistance = 100.0f,
                float surfaceEpsilon = 0.001f)
        : Renderer(
              maxDistance,
              2.0f * surfaceEpsilon
          ),
          maxSteps_(maxSteps),
          surfaceEpsilon_(surfaceEpsilon) {}

    std::optional<Hit> raymarch(const Scene& scene, const Ray& ray, float maxDistance) const;
    std::optional<Hit> raymarch(const Scene& scene, const Ray& ray) const;

private:
    std::optional<Hit> closestHit(const Scene& scene,
                                  const Ray& ray,
                                  float maxDistance) const override;
    std::optional<float> exitDistance(const Object& object,
                                      const Ray& ray,
                                      float maxDistance) const override;

    int maxSteps_;
    float surfaceEpsilon_;
};
