#pragma once

#include "Renders/Renderer.hpp"

class RayTracing final : public Renderer {
public:
    RayTracing(float maxDistance = 100.0f,
               float intersectionEpsilon = 0.001f)
        : Renderer(
              maxDistance,
              2.0f * intersectionEpsilon
          ),
          intersectionEpsilon_(intersectionEpsilon) {}

    std::optional<Hit> raytrace(const Scene& scene,
                                const Ray& ray,
                                float maxDistance) const;
    std::optional<Hit> raytrace(const Scene& scene, const Ray& ray) const;

private:
    std::optional<Hit> closestHit(const Scene& scene,
                                  const Ray& ray,
                                  float maxDistance) const override;
    std::optional<float> exitDistance(const Object& object,
                                      const Ray& ray,
                                      float maxDistance) const override;

    float intersectionEpsilon_;
};
