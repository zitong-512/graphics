#include "Objects/Cube.hpp"

float Cube::sdf(const Vec3& point) const {
    Vec3 q(std::abs(point.x - center_.x) - radius_, std::abs(point.y - center_.y) - radius_, std::abs(point.z - center_.z) - radius_);

    float x = std::max(q.x, 0.0f);
    float y = std::max(q.y, 0.0f);
    float z = std::max(q.z, 0.0f);

    float outside = std::sqrt(x * x + y * y + z * z);
    float inside = std::min(std::max(q.x, std::max(q.y, q.z)), 0.0f);

    return outside + inside;
}
