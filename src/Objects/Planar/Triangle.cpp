#include "Objects/Planar/Triangle.hpp"

#include "Objects/Plane.hpp"

#include <algorithm>
#include <cmath>

float Triangle::sdf(const Vec3& point) const {
    const float planeDistance = sdfToPlane(point);
    const Vec3 projected = projectOntoPlane(point);
    const Vec2 uv = Plane::worldToUV(projected, origin(), edgeU_, edgeV_);

    float planarDistance = 0.0f;
    if (uv.x < 0.0f || uv.y < 0.0f || uv.x + uv.y > 1.0f) {
        const Vec3 vertex1 = origin() + edgeU_;
        const Vec3 vertex2 = origin() + edgeV_;
        const Vec3 oppositeEdge = vertex2 - vertex1;

        const float parameterU = std::clamp(
            dot(projected - origin(), edgeU_) / dot(edgeU_, edgeU_),
            0.0f,
            1.0f
        );
        const float parameterV = std::clamp(
            dot(projected - origin(), edgeV_) / dot(edgeV_, edgeV_),
            0.0f,
            1.0f
        );
        const float parameterOpposite = std::clamp(
            dot(projected - vertex1, oppositeEdge)
                / dot(oppositeEdge, oppositeEdge),
            0.0f,
            1.0f
        );

        planarDistance = std::min({
            length(projected - (origin() + parameterU * edgeU_)),
            length(projected - (origin() + parameterV * edgeV_)),
            length(projected - (vertex1 + parameterOpposite * oppositeEdge))
        });
    }

    return std::sqrt(
        planeDistance * planeDistance + planarDistance * planarDistance
    );
}
