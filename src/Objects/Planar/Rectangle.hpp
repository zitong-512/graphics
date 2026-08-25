#pragma once

#include "Objects/Planar/PlanarObject.hpp"

#include <utility>

class Rectangle final : public PlanarObject {
public:
    // edgeU and edgeV start at origin and are expected to be perpendicular.
    Rectangle(Vec3 origin,
              Vec3 edgeU,
              Vec3 edgeV,
              Material material,
              std::shared_ptr<const Shader> shader)
        : PlanarObject(
              origin,
              cross(edgeU, edgeV),
              std::move(material),
              std::move(shader),
              edgeU,
              edgeV
          ),
          edgeU_(edgeU),
          edgeV_(edgeV) {}

    float sdf(const Vec3& point) const override;

private:
    Vec3 edgeU_;
    Vec3 edgeV_;
};
