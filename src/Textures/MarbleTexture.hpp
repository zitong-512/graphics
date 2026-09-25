#pragma once

#include "Textures/Texture.hpp"

class MarbleTexture final : public Texture {
public:
    MarbleTexture(Vec3 baseColor,
                  Vec3 veinColor,
                  float scale = 4.0f,
                  float bandFrequency = 8.0f,
                  float distortion = 5.0f);

    Vec3 sample(const Vec2& uv) const override;

private:
    Vec3 baseColor_;
    Vec3 veinColor_;
    float scale_;
    float bandFrequency_;
    float distortion_;
};
