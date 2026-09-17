#include "Objects/Cube.hpp"

#include <algorithm>

float Cube::sdf(const Vec3& point) const {
    Vec3 q(std::abs(point.x - center_.x) - radius_, std::abs(point.y - center_.y) - radius_, std::abs(point.z - center_.z) - radius_);

    float x = std::max(q.x, 0.0f);
    float y = std::max(q.y, 0.0f);
    float z = std::max(q.z, 0.0f);

    float outside = std::sqrt(x * x + y * y + z * z);
    float inside = std::min(std::max(q.x, std::max(q.y, q.z)), 0.0f);

    return outside + inside;
}
std::optional<Hit> Cube::hit(const Ray& ray,
                             float intersectionEpsilon,
                             float maxDistance) const {
    const Vec3 boxMin = center_ - Vec3{radius_, radius_, radius_};
    const Vec3 boxMax = center_ + Vec3{radius_, radius_, radius_};

    const float ty1 = dot((boxMin - ray.origin), {0.0f, 1.0f, 0.0f}) / dot(ray.direction, {0.0f, 1.0f, 0.0f});
    const float ty2 = dot((boxMax - ray.origin), {0.0f, 1.0f, 0.0f}) / dot(ray.direction, {0.0f, 1.0f, 0.0f});

    const float tNear = std::max({
        std::min(ty1, ty2)
    });
    const float tFar = std::min({
        std::max(ty1, ty2)
    });

    if (tNear > tFar || tFar < intersectionEpsilon) {
        return std::nullopt;
    }

    const float t = tNear >= intersectionEpsilon ? tNear : tFar;
    if (t > maxDistance) {
        return std::nullopt;
    }

    Hit hit;
    hit.t = t;
    hit.point = ray.at(t);
    if (t == ty1) {
        hit.normal = {0.0f, -1.0f, 0.0f};
    } else {
        hit.normal = {0.0f, 1.0f, 0.0f};
    }
    hit.uv = {0.0f, 0.0f};
    hit.object = this;
    return hit;
}

 
 
