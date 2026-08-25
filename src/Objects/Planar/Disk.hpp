#pragma once

#include "Objects/Planar/PlanarObject.hpp"

#include <optional>
#include <utility>

class Disk final : public PlanarObject {
public:
    Disk(Vec3 center,
         Vec3 normal,
         float radius,
         Material material,
         std::shared_ptr<const Shader> shader,
         std::optional<Vec3> textureU = std::nullopt,
         std::optional<Vec3> textureV = std::nullopt)
        : PlanarObject(
              center,
              normal,
              std::move(material),
              std::move(shader),
              std::move(textureU),
              std::move(textureV)
          ),
          radius_(radius) {}

    float sdf(const Vec3& point) const override;

private:
    float radius_;
};
