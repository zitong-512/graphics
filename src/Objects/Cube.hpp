#pragma once

#include "Objects/Object.hpp"

#include <utility>

class Cube final : public Object {
public:
    Cube(Vec3 center,
         float radius,
         Material material,
         std::shared_ptr<const Shader> shader)
        : Object(std::move(material), std::move(shader)),
          center_(center),
          radius_(radius) {}

    void setCenter(const Vec3& center) { center_ = center; }
    const Vec3& getCenter() const { return center_; }

    float sdf(const Vec3& point) const override;
    std::optional<Hit> hit(const Ray& ray, float intersectionEpsilon, float maxDistance) const override;

private:
    Vec3 center_;
    float radius_;
};
