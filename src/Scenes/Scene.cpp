#include "Scenes/Scene.hpp"

  #include <limits>
  #include <memory>

  Scene::Scene()
      : camera_(
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, -1.0f},
            {0.0f, 1.0f, 0.0f},
            8.0f / 3.0f,
            2.0f
        )
  {
      objects_.push_back(
          std::make_shared<Donut>(
              Vec3{0.0f, 0.0f, -3.0f},
              1.0f,
              0.3f
          )
      );
  }

  Hit Scene::sdf(const Vec3& point) const {
      float closestDistance = std::numeric_limits<float>::infinity();
      const Object* closestObject = nullptr;

      for (const auto& object : objects_) {
          const float distance = object->sdf(point);

          if (distance < closestDistance) {
              closestDistance = distance;
              closestObject = object.get();
          }
      }

      return {
          closestDistance,
          point,
          Vec3{},
          closestObject
      };
  }

  Vec3 Scene::normal(const Vec3& point, const Object& object) const {
      return object.normal(point);
  }