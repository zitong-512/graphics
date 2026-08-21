#pragma once

#include "Shaders/Shader.hpp"

class ToonShader : public Shader {
public:
    ToonShader(Vec3 objectColor = {0.85f, 0.4f, 0.15f},
                  Vec3 ambientLight = {0.35f, 0.35f, 0.35f})
        : objectColor_(objectColor), ambientLight_(ambientLight) {}

    Vec3 shade(const Hit& hit) const override;

private:
    Vec3 objectColor_;
    Vec3 ambientLight_;
};
