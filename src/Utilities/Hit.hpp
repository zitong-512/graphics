#pragma once

#include "Utilities/Vec2.hpp"
#include "Utilities/Vec3.hpp"

class Object;

struct Hit {
    float t = 0.0f;
    Vec3 point;
    Vec3 normal;
    Vec2 uv;
    const Object* object = nullptr;
};
