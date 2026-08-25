#include "Objects/Cone.hpp"

#include <algorithm>
#include <cmath>

float Cone::sdf(const Vec3& point) const {
    const Vec3 local = point - center_;
    const float radial = std::sqrt(local.x * local.x + local.y * local.y);

    // Exact SDF for a capped cone centered on the z-axis. The base is at
    // -halfHeight_ and the apex is at +halfHeight_.
    const float capRadius = local.z < 0.0f ? radius_ : 0.0f;
    const float caX = radial - std::min(radial, capRadius);
    const float caZ = std::fabs(local.z) - halfHeight_;

    const float slopeX = -radius_;
    const float slopeZ = 2.0f * halfHeight_;
    const float slopeLengthSquared = slopeX * slopeX + slopeZ * slopeZ;
    const float projection = std::clamp(
        ((-radial) * slopeX + (halfHeight_ - local.z) * slopeZ)
            / slopeLengthSquared,
        0.0f,
        1.0f
    );
    const float cbX = radial + slopeX * projection;
    const float cbZ = local.z - halfHeight_ + slopeZ * projection;

    const float capDistanceSquared = caX * caX + caZ * caZ;
    const float sideDistanceSquared = cbX * cbX + cbZ * cbZ;
    const float sign = cbX < 0.0f && caZ < 0.0f ? -1.0f : 1.0f;

    return sign * std::sqrt(std::min(capDistanceSquared, sideDistanceSquared));
}
