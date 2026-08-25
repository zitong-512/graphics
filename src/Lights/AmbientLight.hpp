#pragma once

#include "Lights/Light.hpp"

class AmbientLight final : public Light {
public:
    explicit AmbientLight(Vec3 color) : Light(color) {}
};