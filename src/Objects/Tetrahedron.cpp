#include "Objects/Tetrahedron.hpp"
#include <algorithm>

  float Tetrahedron::sdf(const Vec3& point) const {
      const Vec3 local = point - center_;

      const float face1 = -local.x - local.y - local.z;
      const float face2 = -local.x + local.y + local.z;
      const float face3 =  local.x - local.y + local.z;
      const float face4 =  local.x + local.y - local.z;

      constexpr float inverseSqrtThree = 0.57735026919f;
      return std::max({face1, face2, face3, face4})
           * inverseSqrtThree
           - radius_;
  }
