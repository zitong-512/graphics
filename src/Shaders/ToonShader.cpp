#include "Shaders/ToonShader.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

Vec3 ToonShader::shade(
    const Hit& hit,
    const Material& material,
    const Camera& camera,
    const std::vector<LightPtr>& lights
) const {
    if (levels_ < 2) {
        throw std::invalid_argument("Toon shader requires at least two levels");
    }

    const Vec3 smooth = BlinnPhongShader::shade(hit, material, camera, lights);
    const float steps = static_cast<float>(levels_ - 1);
    const auto quantize = [steps](float value) {
        return std::round(std::clamp(value, 0.0f, 1.0f) * steps) / steps;
    };

    return {quantize(smooth.x), quantize(smooth.y), quantize(smooth.z)};
}
