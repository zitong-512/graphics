#pragma once

#include "Utilities/Hit.hpp"

class Shader {
public:
    virtual ~Shader() = default;
    virtual Vec3 shade(const Hit& hit) const = 0;
};
