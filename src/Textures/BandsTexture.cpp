#include "Textures/BandsTexture.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

BandsTexture::BandsTexture(Material material0, Material material1, int bandCount)
    : material0_(std::move(material0)),
      material1_(std::move(material1)),
      bandCount_(bandCount) {
    if (bandCount_ <= 0) {
        throw std::invalid_argument(
            "Bands texture band count must be positive"
        );
    }
}

Material BandsTexture::sample(const Vec2& uv) const {
    const float wobble =
        0.05f * std::sin(20.0f * uv.x) + std::sin(7.5f * uv.x);
    float v = std::clamp(uv.y + wobble, 0.0f, 1.0f);
    //float v = uv.y;

    float bandLength = 1 / (float) bandCount_;

    int n = 0;
    for(int i = 0; i * bandLength < v; i++){
        n = i;
    }

    if (n % 2 == 0){
        return material0_;
    }
    Material material = material1_;
    material.objectColor = material.objectColor * (1.0f - (v - n * bandLength) / bandLength);
    return material;
}
