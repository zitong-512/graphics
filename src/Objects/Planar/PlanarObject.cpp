#include "Objects/Planar/PlanarObject.hpp"
#include "Objects/Plane.hpp"
#include "Utilities/PlanarTextureBasis.hpp"

#include <utility>

PlanarObject::PlanarObject(Vec3 origin,
                           Vec3 normal,
                           Material material,
                           std::shared_ptr<const Shader> shader,
                           std::optional<Vec3> textureU,
                           std::optional<Vec3> textureV)
    : Object(std::move(material), std::move(shader)),
      origin_(origin),
      normal_(normalize(normal)) {
    const auto basis = makePlanarTextureBasis(normal_, textureU, textureV);
    textureU_ = basis.first;
    textureV_ = basis.second;
}

Vec3 PlanarObject::normal(const Vec3&) const {
    return normal_;
}

Vec2 PlanarObject::textureCoordinates(const Vec3& point) const {
    return Plane::worldToUV(point, origin_, textureU_, textureV_);
}

float PlanarObject::sdfToPlane(const Vec3& point) const {
    return dot(point - origin_, normal(point));
}

Vec3 PlanarObject::projectOntoPlane(const Vec3& point) const {
    return point - sdfToPlane(point) * normal(point);
}
