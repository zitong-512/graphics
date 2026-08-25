#include "Objects/Donut.hpp"

float Donut::sdf(const Vec3& point) const {
    Vec3 local = point - center_;
    const float radial = sqrt(local.x * local.x + local.z * local.z) - big_radius_;
    const float distance = sqrt(radial * radial + local.y * local.y) - small_radius_;
    return distance;
}

