#pragma once

#include "Objects/Planar/PlanarObject.hpp"

#include <utility>

class Triangle final : public PlanarObject {
public:
    Triangle(Vec3 vertex0,
             Vec3 vertex1,
             Vec3 vertex2,
             Material material,
             std::shared_ptr<const Shader> shader)
        : PlanarObject(
              vertex0,
              cross(vertex1 - vertex0, vertex2 - vertex0),
              std::move(material),
              std::move(shader),
              vertex1 - vertex0,
              vertex2 - vertex0
          ),
          edgeU_(vertex1 - vertex0),
          edgeV_(vertex2 - vertex0) {}

    float sdf(const Vec3& point) const override;

private:
    Vec3 edgeU_;
    Vec3 edgeV_;
};
