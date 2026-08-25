#pragma once

#include "Objects/Object.hpp"

#include <utility>

class Tetrahedron final : public Object {
public:
    Tetrahedron(Vec3 center,
                float radius,
                Material material,
                std::shared_ptr<const Shader> shader)
        : Object(std::move(material), std::move(shader)),
          center_(center),
          radius_(radius) {}

    float sdf(const Vec3& point) const override;

private:
    Vec3 center_;
    float radius_;
};
