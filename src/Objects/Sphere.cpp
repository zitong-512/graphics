#include "Objects/Sphere.hpp"

float Sphere::sdf(const Vec3& point) const {
    return length(point - center_) - radius_;
}

Vec3 Sphere::normal(const Vec3& point) const {
    return normalize(point - center_);
}
