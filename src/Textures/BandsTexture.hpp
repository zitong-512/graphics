#pragma once

#include "Textures/Texture.hpp"

class BandsTexture final : public Texture {
public:
    BandsTexture(Vec3 color0, Vec3 color1, int bandCount = 10);

    Vec3 sample(const Vec2& uv) const override;

private:
    Vec3 color0_;
    Vec3 color1_;
    int bandCount_;
};
