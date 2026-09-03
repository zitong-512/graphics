#pragma once

#include "Textures/Texture.hpp"
#include "Utilities/Vec2.hpp"
#include "Utilities/Vec3.hpp"

#include <utility>

struct Material {
    Material() = default;

    Material(Vec3 objectColorValue,
             Vec3 specularColorValue,
             float shininessValue,
             TexturePtr colorTextureValue = nullptr,
             float reflectivenessValue = 0.0f,
             float transmissivityValue = 0.0f,
             float refractiveIndexValue = 1.5f)
        : objectColor(objectColorValue),
          specularColor(specularColorValue),
          shininess(shininessValue),
          colorTexture(std::move(colorTextureValue)),
          reflectiveness(reflectivenessValue),
          transmissivity(transmissivityValue),
          refractiveIndex(refractiveIndexValue) {}

    Vec3 objectColor{0.4f, 0.4f, 0.85f};
    Vec3 specularColor{1.0f, 1.0f, 1.0f};
    float shininess = 32.0f;
    TexturePtr colorTexture;
    float reflectiveness = 0.0f;
    float transmissivity = 0.0f;
    float refractiveIndex = 1.5f;

    Vec3 colorAt(const Vec2& uv) const {
        return colorTexture ? colorTexture->sample(uv) : objectColor;
    }
};
