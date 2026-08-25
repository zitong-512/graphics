#pragma once

#include "Lights/Light.hpp"

class PointLight final : public Light {
public:
    PointLight(Vec3 position, Vec3 color)
        : Light(color), position_(position) {}

    const Vec3& position() const { return position_; }

private:
    Vec3 position_;
};
