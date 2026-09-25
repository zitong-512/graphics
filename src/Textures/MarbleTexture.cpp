#include "Textures/MarbleTexture.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace {
constexpr float pi = 3.14159265358979323846f;

float fade(float t) {
    return t * t * (3.0f - 2.0f * t);
}

float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

float randomValue(int x, int y, int z) {
    const float value = std::sin(
        static_cast<float>(x) * 127.1f
        + static_cast<float>(y) * 311.7f
        + static_cast<float>(z) * 74.7f
    ) * 43758.5453f;
    return value - std::floor(value);
}

float valueNoise(const Vec3& point) {
    const int x0 = static_cast<int>(std::floor(point.x));
    const int y0 = static_cast<int>(std::floor(point.y));
    const int z0 = static_cast<int>(std::floor(point.z));

    const float tx = fade(point.x - static_cast<float>(x0));
    const float ty = fade(point.y - static_cast<float>(y0));
    const float tz = fade(point.z - static_cast<float>(z0));

    const float x00 = lerp(randomValue(x0, y0, z0),
                           randomValue(x0 + 1, y0, z0), tx);
    const float x10 = lerp(randomValue(x0, y0 + 1, z0),
                           randomValue(x0 + 1, y0 + 1, z0), tx);
    const float x01 = lerp(randomValue(x0, y0, z0 + 1),
                           randomValue(x0 + 1, y0, z0 + 1), tx);
    const float x11 = lerp(randomValue(x0, y0 + 1, z0 + 1),
                           randomValue(x0 + 1, y0 + 1, z0 + 1), tx);

    const float y0Value = lerp(x00, x10, ty);
    const float y1Value = lerp(x01, x11, ty);
    return lerp(y0Value, y1Value, tz);
}

float fractalNoise(Vec3 point) {
    float result = 0.0f;
    float amplitude = 0.5f;

    for (int octave = 0; octave < 5; ++octave) {
        result += amplitude * valueNoise(point);
        point = point * 2.0f;
        amplitude *= 0.5f;
    }

    return result;
}

Vec3 mix(const Vec3& a, const Vec3& b, float t) {
    return a * (1.0f - t) + b * t;
}
} // namespace

MarbleTexture::MarbleTexture(Vec3 baseColor,
                             Vec3 veinColor,
                             float scale,
                             float bandFrequency,
                             float distortion)
    : baseColor_(baseColor),
      veinColor_(veinColor),
      scale_(scale),
      bandFrequency_(bandFrequency),
      distortion_(distortion) {
    if (scale_ <= 0.0f) {
        throw std::invalid_argument("Marble texture scale must be positive");
    }
    if (bandFrequency_ <= 0.0f) {
        throw std::invalid_argument(
            "Marble texture band frequency must be positive"
        );
    }
    if (distortion_ < 0.0f) {
        throw std::invalid_argument(
            "Marble texture distortion cannot be negative"
        );
    }
}

Vec3 MarbleTexture::sample(const Vec2& uv) const {
    const float longitude = 2.0f * pi * (uv.x - 0.5f);
    const float latitude = pi * (0.5f - uv.y);
    const float cosLatitude = std::cos(latitude);

    // Reconstruct the sphere's local surface direction. Sampling noise in
    // this 3D space keeps the pattern continuous across the UV seam.
    const Vec3 direction{
        cosLatitude * std::cos(longitude),
        std::sin(latitude),
        cosLatitude * std::sin(longitude)
    };

    const float turbulence = fractalNoise(direction * scale_);
    const float bandPosition =
        direction.x + 0.35f * direction.y + 0.2f * direction.z;
    const float wave = 0.5f + 0.5f * std::sin(
        bandFrequency_ * bandPosition + distortion_ * turbulence
    );

    // A power curve narrows the bright portions into marble-like veins.
    const float veinAmount = std::clamp(std::pow(wave, 3.0f), 0.0f, 1.0f);
    return mix(baseColor_, veinColor_, veinAmount);
}
