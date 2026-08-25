#pragma once

#include "Shaders/Shader.hpp"

class BlinnPhongShader : public Shader {
public:
    Vec3 shade(const Hit& hit,
               const Material& material,
               const Camera& camera,
               const std::vector<LightPtr>& lights) const override;
};
