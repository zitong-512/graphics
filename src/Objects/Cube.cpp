#include "Objects/Cube.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

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

    float tNear = -std::numeric_limits<float>::infinity();
    float tFar = std::numeric_limits<float>::infinity();
    Vec3 nearNormal;
    Vec3 farNormal;

    const auto intersectSlab = [&](float origin, float direction,
                                   float minimum, float maximum,
                                   const Vec3& minimumNormal,
                                   const Vec3& maximumNormal) {
        constexpr float parallelEpsilon = 1.0e-8f;
        if (std::abs(direction) <= parallelEpsilon) {
            return origin >= minimum && origin <= maximum;
        }

        float t1 = (minimum - origin) / direction;
        float t2 = (maximum - origin) / direction;
        Vec3 n1 = minimumNormal;
        Vec3 n2 = maximumNormal;
        if (t1 > t2) {
            std::swap(t1, t2);
            std::swap(n1, n2);
        }

        if (t1 > tNear) {
            tNear = t1;
            nearNormal = n1;
        }
        if (t2 < tFar) {
            tFar = t2;
            farNormal = n2;
        }
        return tNear <= tFar;
    };

    if (!intersectSlab(ray.origin.x, ray.direction.x, boxMin.x, boxMax.x,
                       {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}) ||
        !intersectSlab(ray.origin.y, ray.direction.y, boxMin.y, boxMax.y,
                       {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}) ||
        !intersectSlab(ray.origin.z, ray.direction.z, boxMin.z, boxMax.z,
                       {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f, 1.0f})) {
        return std::nullopt;
    }

    const bool useNear = tNear > intersectionEpsilon;
    const float t = useNear ? tNear : tFar;
    if (t <= intersectionEpsilon || t >= maxDistance) { return std::nullopt; }

    Hit hit;
    hit.t = t;
    hit.point = ray.at(t);
    hit.normal = useNear ? nearNormal : farNormal;
    hit.uv = {0.0f, 0.0f};
    hit.object = this;
    return hit;
}

 
 
