#pragma once

#include "Objects/Sphere.hpp"
#include "Utilities/Camera.hpp"

class Scene {
public:
    Scene();

    float sdf(const Vec3& point) const;
    Vec3 normal(const Vec3& point) const;
    Vec3 background() const { return {0.05f, 0.07f, 0.12f}; }
    const Camera& camera() const { return camera_; }

private:
    Camera camera_;
    Sphere sphere_;
};
