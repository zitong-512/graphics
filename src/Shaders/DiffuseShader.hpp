#pragma once

#include "Shaders/Shader.hpp"

class DiffuseShader: public Shader {
public:
    DiffuseShader(Vec3 objectColor = {0.85f, 0.4f, 0.15f},
                  Vec3 ambientLight = {0.55f, 0.55f, 0.85f},
                  Vec3 positionLight = {1.0f, 1.0f, 1.0f})
        : objectColor_(objectColor), ambientLight_(ambientLight), positionLight_(positionLight) {}

    Vec3 shade(const Hit& hit) const override;

private:
    Vec3 objectColor_;
    Vec3 ambientLight_;
    Vec3 positionLight_;
};
