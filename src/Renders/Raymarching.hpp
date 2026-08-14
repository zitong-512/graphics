#pragma once

#include "Scenes/Scene.hpp"
#include "Shaders/Shader.hpp"
#include "Utilities/Hit.hpp"
#include "Utilities/Ray.hpp"

class Raymarching {
public:
    Raymarching(int maxSteps = 128, float maxDistance = 100.0f,
                float surfaceEpsilon = 0.001f)
        : maxSteps_(maxSteps),
          maxDistance_(maxDistance),
          surfaceEpsilon_(surfaceEpsilon) {}

    Vec3 color(const Scene& scene, const Shader& shader, const Ray& ray) const;

private:
    int maxSteps_;
    float maxDistance_;
    float surfaceEpsilon_;
};
