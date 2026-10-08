#pragma once

#include <Textures/Texture.hpp>
#include <Materials/Material.hpp>

class BandsTextureColor final : public MaterialTexture {
public:
    BandsTextureColor(Material material0, Material material1, int bandCount = 10);

    Material sample(const Vec2& uv) const override;

private:
    Material material0_;
    Material material1_;
    int bandCount_;
};
