#pragma once

#include <Materials/Material.hpp>

#include "Textures/Texture.hpp"

class BandsTexture final : public MaterialTexture {
public:
    BandsTexture(Material material0, Material material1, int bandCount = 10);

    Material sample(const Vec2& uv) const override;

private:
    Material material0_;
    Material material1_;
    int bandCount_;
};
