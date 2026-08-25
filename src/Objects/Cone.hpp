#pragma once

#include "Objects/Object.hpp"

#include <utility>

class Cone final : public Object {
public:
    Cone(Vec3 center,
         float radius,
         float height,
         Material material,
         std::shared_ptr<const Shader> shader)
        : Object(std::move(material), std::move(shader)),
          center_(center),
          radius_(radius),
          halfHeight_(height * 0.5f) {}

    float sdf(const Vec3& point) const override;

private:
    Vec3 center_;
    float radius_;
    float halfHeight_;
};