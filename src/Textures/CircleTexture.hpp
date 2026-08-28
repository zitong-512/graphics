#pragma once

#include "Textures/Texture.hpp"

class CircleTexture final : public Texture {
public:
    CircleTexture(Vec3 color0, Vec3 color1, Vec3 color2, Vec3 color3, Vec3 color4,  Vec3 color5, Vec3 color6, Vec3 color7, float radius = 1.0f, Vec2 center = Vec2(0.0f, 0.0f));

    Vec3 sample(const Vec2& uv) const override;

private:
    Vec3 color0_;
    Vec3 color1_;
    Vec3 color2_;
    Vec3 color3_;
    Vec3 color4_;
    Vec3 color5_;
    Vec3 color6_;
    Vec3 color7_;
    float radius_;
    Vec2 center_;
};
