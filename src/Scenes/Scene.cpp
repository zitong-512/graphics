#include "Scenes/Scene.hpp"

#include <limits>
#include <utility>

Scene::Scene(Camera camera,
             Vec3 background,
             std::vector<LightPtr> lights,
             std::vector<ObjectPtr> objects,
             int sample)
    : camera_(std::move(camera)),
      background_(background),
      lights_(std::move(lights)),
      objects_(std::move(objects)),
      sample_(sample) {}

std::pair<float, const Object*> Scene::sdf(const Vec3& point) const {
    float closestDistance = std::numeric_limits<float>::infinity();
    const Object* closestObject = nullptr;

    for (const ObjectPtr& object : objects_) {
        if (!object) {
            continue;
        }

        const float distance = object->sdf(point);
        if (distance < closestDistance) {
            closestDistance = distance;
            closestObject = object.get();
        }
    }

    return {closestDistance, closestObject};
}