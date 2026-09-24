#include "Objects/Cylinder.hpp"

// Cylinder TODOs:
// 1. Give sdf() a real cylinder distance.
// 2. Give the cylinder useful UV coordinates.

float Cylinder::sdf(const Vec3&) const {
    return 0.0f;
}

Vec3 Cylinder::normal(const Vec3& point) const {
    const float zMin = center_.z - 0.5f * height_;
    const float zMax = center_.z + 0.5f * height_;
    const Vec3 radial{point.x - center_.x, point.y - center_.y, 0.0f};
    const float radialLength = length(radial);

    const float distanceToBottom = std::abs(point.z - zMin);
    const float distanceToTop = std::abs(point.z - zMax);
    const float distanceToWall = std::abs(radialLength - radius_);

    if (distanceToBottom <= distanceToWall && distanceToBottom <= distanceToTop) {
        return {0.0f, 0.0f, -1.0f};
    }
    if (distanceToTop <= distanceToWall) {
        return {0.0f, 0.0f, 1.0f};
    }
    // A wall normal is undefined on the cylinder axis. This fallback only
    // matters for points that are not on a non-degenerate cylinder's wall.
    if (radialLength == 0.0f) {
        return {1.0f, 0.0f, 0.0f};
    }
    return radial / radialLength;
}

std::optional<Hit> Cylinder::hit(const Ray& ray,
                                 float intersectionEpsilon,
                                 float maxDistance) const {
    constexpr float parallelEpsilon = 1.0e-8f;
    const float zMin = center_.z - 0.5f * height_;
    const float zMax = center_.z + 0.5f * height_;

    float closestT = maxDistance;
    Vec3 closestNormal;
    bool foundHit = false;

    const auto considerHit = [&](float t, const Vec3& normal) {
        if (t > intersectionEpsilon && t < closestT) {
            closestT = t;
            closestNormal = normal;
            foundHit = true;
        }
    };

    // Intersect the curved wall in the XY plane.
    const Vec2 direction = planar(ray.direction);
    const Vec2 offset = planar(ray.origin) - planar(center_);
    const float a = dot(direction, direction);

    if (a > parallelEpsilon) {
        const float b = 2.0f * dot(direction, offset);
        const float c = dot(offset, offset) - radius_ * radius_;
        const float discriminant = b * b - 4.0f * a * c;

        if (discriminant >= 0.0f) {
            const float root = std::sqrt(discriminant);
            const float t1 = (-b - root) / (2.0f * a);
            const float t2 = (-b + root) / (2.0f * a);

            const auto considerWallHit = [&](float t) {
                const Vec3 point = ray.at(t);
                if (point.z >= zMin && point.z <= zMax) {
                    considerHit(
                        t,
                        normalize(Vec3{
                            point.x - center_.x,
                            point.y - center_.y,
                            0.0f
                        })
                    );
                }
            };

            considerWallHit(t1);
            considerWallHit(t2);
        }
    }

    // Intersect the two circular caps.
    if (std::abs(ray.direction.z) > parallelEpsilon) {
        const auto considerCapHit = [&](float z, const Vec3& normal) {
            const float t = (z - ray.origin.z) / ray.direction.z;
            const Vec3 point = ray.at(t);
            const float dx = point.x - center_.x;
            const float dy = point.y - center_.y;

            if (dx * dx + dy * dy <= radius_ * radius_) {
                considerHit(t, normal);
            }
        };

        considerCapHit(zMin, {0.0f, 0.0f, -1.0f});
        considerCapHit(zMax, {0.0f, 0.0f, 1.0f});
    }

    if (!foundHit) {
        return std::nullopt;
    }

    Hit hit;
    hit.t = closestT;
    hit.point = ray.at(closestT);
    hit.normal = closestNormal;
    hit.uv = {0.0f, 0.0f};
    hit.object = this;
    return hit;
}
