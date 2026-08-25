#pragma once

#include "Objects/Object.hpp"

#include <memory>
#include <optional>

class PlanarObject : public Object {
public:
    PlanarObject(Vec3 origin,
                 Vec3 normal,
                 Material material,
                 std::shared_ptr<const Shader> shader,
                 std::optional<Vec3> textureU = std::nullopt,
                 std::optional<Vec3> textureV = std::nullopt);

    Vec3 normal(const Vec3& point) const override;
    Vec2 textureCoordinates(const Vec3& point) const override;

protected:
    float sdfToPlane(const Vec3& point) const;
    Vec3 projectOntoPlane(const Vec3& point) const;

    const Vec3& origin() const { return origin_; }

private:
    Vec3 origin_;
    Vec3 normal_;
    Vec3 textureU_;
    Vec3 textureV_;
};
