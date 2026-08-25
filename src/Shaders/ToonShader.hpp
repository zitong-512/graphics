#pragma once

#include "Shaders/BlinnPhongShader.hpp"

class ToonShader : public BlinnPhongShader {
public:
    explicit ToonShader(int levels = 3) : levels_(levels) {}

    Vec3 shade(const Hit& hit,
               const Material& material,
               const Camera& camera,
               const std::vector<LightPtr>& lights) const override;

private:
    int levels_;
};
