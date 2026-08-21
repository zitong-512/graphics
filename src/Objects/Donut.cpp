#include "Objects/Donut.hpp"

float Donut::sdf(const Vec3& point) const {
    return length(point - center_) - (big_radius_ + small_radius_);
}

Vec3 Donut::normal(const Vec3& point) const {
    return normalize(point - center_);
}
