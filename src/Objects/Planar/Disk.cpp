#include "Objects/Planar/Disk.hpp"

#include <algorithm>
#include <cmath>

float Disk::sdf(const Vec3& point) const {
    const float planeDistance = sdfToPlane(point);
    const Vec3 projected = projectOntoPlane(point);
    const float planarDistance = std::max(
        length(projected - origin()) - radius_,
        0.0f
    );

    return std::sqrt(
        planeDistance * planeDistance + planarDistance * planarDistance
    );
}
