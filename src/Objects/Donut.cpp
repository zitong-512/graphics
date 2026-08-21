#include "Objects/Donut.hpp"

float Donut::sdf(const Vec3& point) const {
    Vec3 local = point - center_;
    const float radial = sqrt(local.x * local.x + local.z * local.z) - big_radius_;
    const float distance = sqrt(radial * radial + local.y * local.y) - small_radius_;
    return distance;
}

Vec3 Donut::normal(const Vec3& point) const {
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
