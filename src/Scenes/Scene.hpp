#pragma once

#include <memory>
#include <vector>
#include "Objects/Sphere.hpp"
#include "Objects/Donut.hpp"
#include "Utilities/Camera.hpp"
#include "Utilities/Hit.hpp"

class Scene {
public:
    Scene();

    Hit sdf(const Vec3& point) const;
    Vec3 normal(const Vec3& point, const Object& object) const;
    Vec3 background() const { return {0.05f, 0.07f, 0.12f}; }
    const Camera& camera() const { return camera_; }

private:
    Camera camera_;
    std::vector<std::shared_ptr<Object>> objects_;
    //std::vector<std::shared_ptr<Light>> lights_;
    Vec3 background_;
};
