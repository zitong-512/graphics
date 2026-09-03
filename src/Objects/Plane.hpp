#pragma once

#include "Objects/Object.hpp"
#include "Utilities/Vec2.hpp"

#include <optional>
#include <utility>

class Plane final : public Object {
public:
    Plane(Vec3 point,
          Vec3 normal,
          Material material,
          std::shared_ptr<const Shader> shader,
          std::optional<Vec3> textureU = std::nullopt,
          std::optional<Vec3> textureV = std::nullopt);

    float sdf(const Vec3& point) const override;
    std::optional<Hit> hit(const Ray& ray,
                           float intersectionEpsilon,
                           float maxDistance) const override;
    Vec3 normal(const Vec3& point) const override;
    Vec2 textureCoordinates(const Vec3& point) const override;

    static Vec2 worldToUV(const Vec3& point,
                          const Vec3& origin,
                          const Vec3& u,
                          const Vec3& v);

private:
    Vec3 point_;
    Vec3 normal_;
    Vec3 textureU_;
    Vec3 textureV_;
};
