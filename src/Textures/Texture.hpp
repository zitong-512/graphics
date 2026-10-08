#pragma once

#include "Utilities/Vec2.hpp"
#include "Utilities/Vec3.hpp"

#include <memory>

struct Material;

class Texture {
public:
    virtual ~Texture() = default;

    virtual Vec3 sample(const Vec2& uv) const = 0;
};

using TexturePtr = std::shared_ptr<const Texture>;

class MaterialTexture {
public:
    virtual ~MaterialTexture() = default;

    virtual Material sample(const Vec2& uv) const = 0;
};

using MaterialTexturePtr = std::shared_ptr<const MaterialTexture>;
