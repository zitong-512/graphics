#include "Objects/Object.hpp"

#include <utility>

Object::Object(Material material, std::shared_ptr<const Shader> shader)
    : material_(std::move(material)), shader_(std::move(shader)) {}

float Object::transformedSdf(const Vec3& point) const {
    return transform_.minimumScale() * sdf(transform_.pointToLocal(point));
}

std::optional<Hit> Object::transformedHit(const Ray& ray,
                                          float intersectionEpsilon,
                                          float maxDistance) const {
    const Ray localRay{
        transform_.pointToLocal(ray.origin),
        transform_.vectorToLocal(ray.direction)
    };

    std::optional<Hit> result = hit(
        localRay,
        intersectionEpsilon,
        maxDistance
    );
    if (!result) {
        return std::nullopt;
    }

    result->point = ray.at(result->t);
    result->normal = transform_.normalToWorld(result->normal);
    result->object = this;
    return result;
}

Vec3 Object::transformedNormal(const Vec3& point) const {
    const Vec3 localPoint = transform_.pointToLocal(point);
    return transform_.normalToWorld(normal(localPoint));
}

Vec2 Object::transformedTextureCoordinates(const Vec3& point) const {
    return textureCoordinates(transform_.pointToLocal(point));
}

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

std::optional<Hit> Object::hit(const Ray&, float, float) const {
    return std::nullopt;
}

Vec2 Object::textureCoordinates(const Vec3& point) const {
    return {point.x, point.y};
}
