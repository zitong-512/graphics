#include "Objects/Dodecahedron.hpp"

#include <algorithm>
#include <cmath>

float Dodecahedron::sdf(const Vec3& point) const {
    const Vec3 local = point - center_;

    // These are the two nonzero coordinates of the normalized face
    // normals. Symmetry reduces the twelve plane distances to three.
    constexpr float shortCoordinate = 0.52573111212f;
    constexpr float longCoordinate = 0.85065080835f;

    const float absoluteX = std::fabs(local.x);
    const float absoluteY = std::fabs(local.y);
    const float absoluteZ = std::fabs(local.z);
    const float closestFace = std::max({
        shortCoordinate * absoluteY + longCoordinate * absoluteZ,
        shortCoordinate * absoluteX + longCoordinate * absoluteY,
        longCoordinate * absoluteX + shortCoordinate * absoluteZ
    });

    return closestFace - radius_;
}
