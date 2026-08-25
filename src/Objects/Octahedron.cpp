#include "Objects/Octahedron.hpp"

#include <algorithm>
#include <cmath>

/*
 The code is, in disguise, computing the signed distance to 
 each of the eight planes that define the octahedron.
*/

float Octahedron::sdf(const Vec3& point) const {
    const Vec3 local = point - center_;

    /* Naive approach: compute the signed distance to each face */
    /*
    const float face0 =  local.x + local.y + local.z;
    const float face1 =  local.x + local.y - local.z;
    const float face2 =  local.x - local.y + local.z;
    const float face3 =  local.x - local.y - local.z;
    const float face4 = -local.x + local.y + local.z;
    const float face5 = -local.x + local.y - local.z;
    const float face6 = -local.x - local.y + local.z;
    const float face7 = -local.x - local.y - local.z;

    const float closestFace = std::max({
        face0, face1, face2, face3,
        face4, face5, face6, face7
    });
    */

    const float closestFace = std::fabs(local.x)
                            + std::fabs(local.y)
                            + std::fabs(local.z);

    // Normalize the face normal and offset its plane by the center-to-face
    // radius.
    constexpr float inverseSqrtThree = 0.57735026919f;
    return closestFace * inverseSqrtThree - radius_;
}


/* More direct approach: */
/*
float Octahedron::sdf(const Vec3& point) const {
    const Vec3 local = point - center_;



    constexpr float inverseSqrtThree = 0.57735026919f;
    return closestFace * inverseSqrtThree - radius_;
}
*/
