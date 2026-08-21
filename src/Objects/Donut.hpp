#pragma once

#include "Utilities/Vec3.hpp"
#include "Objects/Object.hpp"

class Donut : public Object {
public:
    Donut(Vec3 center, float big_radius, float small_radius) : center_(center), big_radius_(big_radius), small_radius_(small_radius) {}


    float sdf(const Vec3& point) const;
    Vec3 normal(const Vec3& point) const;

private:
    Vec3 center_;
    float big_radius_;
    float small_radius_;
};
