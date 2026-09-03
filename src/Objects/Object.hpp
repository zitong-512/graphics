#pragma once

#include "Materials/Material.hpp"
#include "Shaders/Shader.hpp"
#include "Utilities/Hit.hpp"
#include "Utilities/Ray.hpp"
#include "Utilities/Vec3.hpp"

#include <memory>
#include <optional>

class Object {
public:
    Object(Material material, std::shared_ptr<const Shader> shader);
    virtual ~Object() = default;

    virtual float sdf(const Vec3& point) const = 0;
    virtual std::optional<Hit> hit(const Ray& ray,
                                   float intersectionEpsilon,
                                   float maxDistance) const;
    virtual Vec3 normal(const Vec3& point) const;
    virtual Vec2 textureCoordinates(const Vec3& point) const;

    const Material& material() const { return material_; }
    const Shader& shader() const { return *shader_; }

private:
    Material material_;
    std::shared_ptr<const Shader> shader_;
};

using ObjectPtr = std::shared_ptr<const Object>;
