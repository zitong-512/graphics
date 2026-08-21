#pragma once

#include "Utilities/Vec3.hpp"

class Object;

struct Hit {
    float t = 0.0f;
    Vec3 point;
    Vec3 normal;
    const Object* object = nullptr;
};
