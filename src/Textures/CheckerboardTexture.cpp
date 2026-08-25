#include "Textures/CheckerboardTexture.hpp"

#include <stdexcept>

CheckerboardTexture::CheckerboardTexture(Vec3 color0,
                                         Vec3 color1,
                                         float tileSize)
    : color0_(color0),
      color1_(color1),
      tileSize_(tileSize) {
    if (tileSize_ <= 0.0f) {
        throw std::invalid_argument(
            "Checkerboard texture tile size must be positive"
        );
    }
}

Vec3 CheckerboardTexture::sample(const Vec2&) const {
    return {};
}
