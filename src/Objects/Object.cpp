#include "Objects/Object.hpp"

#include <utility>

Object::Object(Material material, std::shared_ptr<const Shader> shader)
    : material_(std::move(material)), shader_(std::move(shader)) {}

Vec3 Object::normal(const Vec3& point) const {
    constexpr float epsilon = 0.0001f;

    const Vec3 gradient{
        sdf(point + Vec3{epsilon, 0.0f, 0.0f})
            - sdf(point - Vec3{epsilon, 0.0f, 0.0f}),
        sdf(point + Vec3{0.0f, epsilon, 0.0f})
            - sdf(point - Vec3{0.0f, epsilon, 0.0f}),
        sdf(point + Vec3{0.0f, 0.0f, epsilon})
            - sdf(point - Vec3{0.0f, 0.0f, epsilon})
    };

    return normalize(gradient);
}

Vec2 Object::textureCoordinates(const Vec3& point) const {
    return {point.x, point.y};
}
