#pragma once

#include "Objects/Object.hpp"

#include <utility>

class Squorus final : public Object {
public:
    Squorus(Vec3 center,
            float bigR,
            float smallR,
            Material material,
            std::shared_ptr<const Shader> shader)
        : Object(std::move(material), std::move(shader)),
          center_(center),
          bigR_(bigR),
          smallR_(smallR) {}

    float sdf(const Vec3& point) const override;

private:
    Vec3 center_;
    float bigR_;
    float smallR_;
};
