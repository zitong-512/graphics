#pragma once

#include "Utilities/Vec3.hpp"
#include "Objects/Object.hpp"

#include <utility>

class Donut : public Object {
public:
    Donut(Vec3 center,
          float bigRadius,
          float smallRadius,
          Material material,
          std::shared_ptr<const Shader> shader)
        : Object(std::move(material), std::move(shader)),
          center_(center),
          big_radius_(bigRadius),
          small_radius_(smallRadius) {}

    float sdf(const Vec3& point) const override;

private:
    Vec3 center_;
    float big_radius_;
    float small_radius_;
};
