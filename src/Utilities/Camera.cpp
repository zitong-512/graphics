#include "Utilities/Camera.hpp"

Camera::Camera(Vec3 position, Vec3 target, Vec3 up,
               float viewportWidth, float viewportHeight)
    : position_(position),
      forward_(normalize(target - position)),
      right_(normalize(cross(forward_, up))),
      up_(normalize(cross(right_, forward_))),
      viewportWidth_(viewportWidth),
      viewportHeight_(viewportHeight) {}

Ray Camera::rayForPixel(int x, int y, int imageWidth, int imageHeight) const {
    const float halfWidth = viewportWidth_ * 0.5f;
    const float halfHeight = viewportHeight_ * 0.5f;
    const float u = 2.0f * (static_cast<float>(x) + 0.5f) / imageWidth - 1.0f;
    const float v = 1.0f - 2.0f * (static_cast<float>(y) + 0.5f) / imageHeight;

    return {position_, normalize(forward_ + u * halfWidth * right_ + v * halfHeight * up_)};
}
