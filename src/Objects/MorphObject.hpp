#pragma once

#include "Objects/Object.hpp"

#include <utility>

class MorphObject final : public Object {
public:
    MorphObject(ObjectPtr from,
                ObjectPtr to,
                Material material,
                std::shared_ptr<const Shader> shader,
                float blend = 0.0f);

    float sdf(const Vec3& point) const override;

    float blend() const { return blend_; }
    void setBlend(float blend);

private:
    ObjectPtr from_;
    ObjectPtr to_;
    float blend_ = 0.0f;
};
