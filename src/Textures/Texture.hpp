#pragma once

#include "Utilities/Vec2.hpp"
#include "Utilities/Vec3.hpp"

#include <memory>

class Texture {
public:
    virtual ~Texture() = default;

    virtual Vec3 sample(const Vec2& uv) const = 0;
};

using TexturePtr = std::shared_ptr<const Texture>;
