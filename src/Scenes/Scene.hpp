#pragma once

#include "Lights/Light.hpp"
#include "Objects/Object.hpp"
#include "Utilities/Camera.hpp"

#include <utility>
#include <vector>

class Scene {
public:
    Scene(Camera camera,
          Vec3 background,
          std::vector<LightPtr> lights,
          std::vector<ObjectPtr> objects);

    std::pair<float, const Object*> sdf(const Vec3& point) const;

    const Vec3& background() const { return background_; }
    const Camera& camera() const { return camera_; }
    const std::vector<LightPtr>& lights() const { return lights_; }
    const std::vector<ObjectPtr>& objects() const { return objects_; }

private:
    Camera camera_;
    Vec3 background_;
    std::vector<LightPtr> lights_;
    std::vector<ObjectPtr> objects_;
};