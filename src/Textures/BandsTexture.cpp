#include "Textures/BandsTexture.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

BandsTexture::BandsTexture(Vec3 color0, Vec3 color1, int bandCount)
    : color0_(color0),
      color1_(color1),
      bandCount_(bandCount) {
    if (bandCount_ <= 0) {
        throw std::invalid_argument(
            "Bands texture band count must be positive"
        );
    }
}

Vec3 BandsTexture::sample(const Vec2& uv) const {
    const float wobble =
        0.05f * std::sin(20.0f * uv.x);
    float v = std::clamp(uv.y + wobble, 0.0f, 1.0f);
    //float v = uv.y;

    float bandLength = 1 / (float) bandCount_;

    int n = 0;
    for(int i = 0; i * bandLength < v; i++){
        n = i;
    }

    if (n % 2 == 0){
        return color0_;
    }
    return color1_;
}
