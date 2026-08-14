#pragma once

#include "Utilities/Vec3.hpp"

struct Ray {
    Vec3 origin;
    Vec3 direction;

    Vec3 at(float t) const { return origin + t * direction; }
};
