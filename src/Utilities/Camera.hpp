#pragma once

#include "Utilities/Ray.hpp"

class Camera {
public:
    Camera(Vec3 position, Vec3 target, Vec3 up,
           float viewportWidth, float viewportHeight);
    Ray rayForPixel(int x, int y, int imageWidth, int imageHeight) const;
    const Vec3& position() const { return position_; }

private:
    Vec3 position_;
    Vec3 forward_;
    Vec3 right_;
    Vec3 up_;
    float viewportWidth_;
    float viewportHeight_;
};
