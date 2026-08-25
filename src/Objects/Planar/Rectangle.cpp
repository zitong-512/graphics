#include "Objects/Planar/Rectangle.hpp"

#include "Objects/Plane.hpp"

#include <algorithm>
#include <cmath>

float Rectangle::sdf(const Vec3& point) const {
    const float planeDistance = sdfToPlane(point);
    const Vec3 projected = projectOntoPlane(point);
    const Vec2 uv = Plane::worldToUV(projected, origin(), edgeU_, edgeV_);

    float planarDistance = 0.0f;
    if (uv.x < 0.0f || uv.x > 1.0f || uv.y < 0.0f || uv.y > 1.0f) {
        const Vec3 closestPoint = origin()
            + std::clamp(uv.x, 0.0f, 1.0f) * edgeU_
            + std::clamp(uv.y, 0.0f, 1.0f) * edgeV_;
        planarDistance = length(projected - closestPoint);
    }

    return std::sqrt(
        planeDistance * planeDistance + planarDistance * planarDistance
    );
}
