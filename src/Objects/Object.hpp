#pragma once

#include "Utilities/Vec3.hpp"

class Object {
public:
    virtual ~Object() = default;
    virtual float sdf(const Vec3& point) const = 0;
    virtual Vec3 normal(const Vec3& point) const = 0;
};
