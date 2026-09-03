#include "Objects/Plane.hpp"
#include "Utilities/PlanarTextureBasis.hpp"

#include <cmath>
#include <stdexcept>
#include <utility>

Plane::Plane(Vec3 point,
             Vec3 normal,
             Material material,
             std::shared_ptr<const Shader> shader,
             std::optional<Vec3> textureU,
             std::optional<Vec3> textureV)
    : Object(std::move(material), std::move(shader)),
      point_(point),
      normal_(normalize(normal)) {
    const auto basis = makePlanarTextureBasis(normal_, textureU, textureV);
    textureU_ = basis.first;
    textureV_ = basis.second;
}

float Plane::sdf(const Vec3& point) const {
    return dot(point - point_, normal_); // Assuming normal_ is normalized
}

std::optional<Hit> Plane::hit(const Ray& ray, float intersectionEpsilon, float maxDistance) const {
    
    const float t = 0;
    if (t < intersectionEpsilon || t > maxDistance) { 
        return std::nullopt; 
    }
    else {
        Hit hit;
        return hit;
    }
}

Vec3 Plane::normal(const Vec3&) const {
    return normal_;
}

Vec2 Plane::textureCoordinates(const Vec3& point) const {
    return worldToUV(point, point_, textureU_, textureV_);
}

Vec2 Plane::worldToUV(const Vec3& point,
                      const Vec3& origin,
                      const Vec3& u,
                      const Vec3& v) {
    const Vec3 displacement = point - origin;
    const float uu = dot(u, u);
    const float uv = dot(u, v);
    const float vv = dot(v, v);
    const float du = dot(displacement, u);
    const float dv = dot(displacement, v);
    const float determinant = uu * vv - uv * uv;

    constexpr float epsilon = 1.0e-6f;
    if (std::fabs(determinant) <= epsilon * uu * vv) {
        throw std::invalid_argument(
            "Plane UV basis vectors must be linearly independent"
        );
    }

    return {
        (du * vv - dv * uv) / determinant,
        (dv * uu - du * uv) / determinant
    };
}
