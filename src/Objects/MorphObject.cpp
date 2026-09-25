#include "Objects/MorphObject.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>

MorphObject::MorphObject(ObjectPtr from,
                         ObjectPtr to,
                         Material material,
                         std::shared_ptr<const Shader> shader,
                         float blend)
    : Object(std::move(material), std::move(shader)),
      from_(std::move(from)),
      to_(std::move(to)) {
    setBlend(blend);
}

float MorphObject::sdf(const Vec3& point) const {
    return from_->sdf(point) * (1.0f - blend_) + to_->sdf(point) * blend_;
}

void MorphObject::setBlend(float blend) {
    blend_ = blend;
}
