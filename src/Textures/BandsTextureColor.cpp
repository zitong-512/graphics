#include <Textures/BandsTextureColor.hpp>

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

BandsTextureColor::BandsTextureColor(
    Vec3 color0, Vec3 color1, int bandCount)
    : color0_(color0),
      color1_(color1),
      bandCount_(bandCount) {
    if (bandCount_ <= 0) {
        throw std::invalid_argument(std::to_string(bandCount_));
    }
}

Vec3 BandsTextureColor::sample(const Vec2& uv) const {
    const float wobble = 0.05f * std::sin(20.0f * uv.x);
    const float v = std::clamp(uv.y + wobble, 0.0f, 1.0f);
    const float bandLength = 1.0f / static_cast<float>(bandCount_);
    int band = 0;
    for (int i = 0; i * bandLength < v; ++i) {
        band = i;
    }

    if (band % 2 == 0) {
        return color0_;
    }

    return color1_ * (1.0f - (v - band * bandLength) / bandLength);
}
