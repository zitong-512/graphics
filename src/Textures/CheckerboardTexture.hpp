#pragma once

#include "Textures/Texture.hpp"

class CheckerboardTexture final : public Texture {
public:
    CheckerboardTexture(Vec3 color0, Vec3 color1, float tileSize = 1.0f);

    Vec3 sample(const Vec2& uv) const override;

private:
    Vec3 color0_;
    Vec3 color1_;
    float tileSize_;
};
