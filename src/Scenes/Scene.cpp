#include "Scenes/Scene.hpp"

Scene::Scene()
    : camera_({0.0f, 0.0f, 0.0f},
              {0.0f, 0.0f, -1.0f},
              {0.0f, 1.0f, 0.0f},
              8.0f / 3.0f,
              2.0f),
      sphere_({0.0f, 0.0f, -3.0f}, 1.0f) {}

float Scene::sdf(const Vec3& point) const {
    return sphere_.sdf(point);
}

Vec3 Scene::normal(const Vec3& point) const {
    return sphere_.normal(point);
}
