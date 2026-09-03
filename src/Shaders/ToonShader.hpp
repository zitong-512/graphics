#pragma once

#include "Shaders/Shader.hpp"

class ToonShader : public Shader {
public:
    ToonShader(Vec3 objectColor,
                  Vec3 ambientLight)
        : objectColor_(objectColor), ambientLight_(ambientLight) {}

    Vec3 shade(const Hit& hit) const override;

private:
    Vec3 objectColor_;
    Vec3 ambientLight_;
};