#pragma once

#include "Materials/Material.hpp"
#include "Shaders/Shader.hpp"
#include "Utilities/Vec2.hpp"
#include "Utilities/Vec3.hpp"

#include <memory>

class Object {
public:
    Object(Material material, std::shared_ptr<const Shader> shader);
    virtual ~Object() = default;

    virtual float sdf(const Vec3& point) const = 0;
    virtual Vec3 normal(const Vec3& point) const;
    virtual Vec2 textureCoordinates(const Vec3& point) const;

    const Material& material() const { return material_; }
    const Shader& shader() const { return *shader_; }

private:
    Material material_;
    std::shared_ptr<const Shader> shader_;
};

using ObjectPtr = std::shared_ptr<const Object>;
