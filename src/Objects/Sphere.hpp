#pragma once

#include "Objects/Object.hpp"
#include "Utilities/Vec3.hpp"

class Sphere : public Object {
public:
    Sphere(Vec3 center, float radius) : center_(center), radius_(radius) {}

    float sdf(const Vec3& point) const;
    Vec3 normal(const Vec3& point) const;

private:
    Vec3 center_;
    float radius_;
};
