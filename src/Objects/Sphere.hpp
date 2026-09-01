#pragma once

#include "Objects/Object.hpp"

#include <utility>

class Sphere final : public Object {
public:
    Sphere(Vec3 center,
           float radius,
           Material material,
           std::shared_ptr<const Shader> shader)
        : Object(std::move(material), std::move(shader)),
          center_(center),
          radius_(radius) {}

    float sdf(const Vec3& point) const override;
    Vec3 normal(const Vec3& point) const override;
    std::optional<Hit> hit(const Ray& ray,
                           float intersectionEpsilon,
                           float maxDistance) const override;

private:
    Vec3 center_;
    float radius_;
};