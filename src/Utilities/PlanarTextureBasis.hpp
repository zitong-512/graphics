#pragma once

#include "Utilities/Vec3.hpp"

#include <cmath>
#include <optional>
#include <stdexcept>
#include <utility>

inline std::pair<Vec3, Vec3> makePlanarTextureBasis(
    const Vec3& normal,
    const std::optional<Vec3>& textureU,
    const std::optional<Vec3>& textureV
) {
    constexpr float epsilon = 1.0e-6f;

    if (textureU.has_value() != textureV.has_value()) {
        throw std::invalid_argument(
            "Plane texture basis requires both U and V vectors"
        );
    }

    if (textureU && textureV) {
        if (length(*textureU) <= epsilon || length(*textureV) <= epsilon
            || length(cross(*textureU, *textureV)) <= epsilon) {
            throw std::invalid_argument(
                "Plane texture basis vectors must be non-zero and independent"
            );
        }
        return {*textureU, *textureV};
    }

    const Vec3 reference = std::fabs(normal.z) < 0.999f
        ? Vec3{0.0f, 0.0f, 1.0f}
        : Vec3{0.0f, 1.0f, 0.0f};
    const Vec3 u = normalize(cross(reference, normal));
    return {u, cross(normal, u)};
}
