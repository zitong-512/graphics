#include "Textures/BandsTexture.hpp"

#include <algorithm>
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
    const int band = std::min(
        static_cast<int>(uv.y * static_cast<float>(bandCount_)),
        bandCount_ - 1
    );

    if (band % 2 == 0) {
        return color0_;
    }
    return color1_;
}
