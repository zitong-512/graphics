#include "Objects/Squorus.hpp"
#include "Utilities/Vec2.hpp"

#include <algorithm>
#include <cmath>

float Squorus::sdf(const Vec3& point) const {
    const Vec3 local = point - center_;
    const float radial = std::sqrt(local.x * local.x + local.y * local.y)
                       - bigR_;

    const Vec2 distanceToProfile{
        std::fabs(radial) - smallR_,
        std::fabs(local.z) - smallR_
    };
    const Vec2 outside{
        std::max(distanceToProfile.x, 0.0f),
        std::max(distanceToProfile.y, 0.0f)
    };
    const float inside = std::min(
        std::max(distanceToProfile.x, distanceToProfile.y),
        0.0f
    );

    return std::sqrt(outside.x * outside.x + outside.y * outside.y)
         + inside;
}
