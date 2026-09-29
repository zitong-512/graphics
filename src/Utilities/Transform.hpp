#pragma once

#include "Utilities/Mat3.hpp"

#include <algorithm>
#include <cmath>

class Transform {
public:
    Transform() = default;

    Transform(Mat3 linear, Vec3 translation)
        : linear_(linear),
          inverse_(linear.inverse()),
          inverseTranspose_(inverse_.transposed()),
          translation_(translation),
          minimumScale_(1.0f / inverse_.frobeniusNorm()) {}

    static Transform translation(const Vec3& offset) {
        return Transform(Mat3::identity(), offset, 1.0f);
    }

    static Transform scale(const Vec3& factors) {
        const float minimumScale = std::min({
            std::abs(factors.x),
            std::abs(factors.y),
            std::abs(factors.z)
        });
        return Transform(Mat3::scale(factors), {}, minimumScale);
    }

    static Transform rotationX(float angle) {
        return Transform(Mat3::rotationX(angle), {}, 1.0f);
    }

    static Transform rotationY(float angle) {
        return Transform(Mat3::rotationY(angle), {}, 1.0f);
    }

    static Transform rotationZ(float angle) {
        return Transform(Mat3::rotationZ(angle), {}, 1.0f);
    }

    Vec3 pointToLocal(const Vec3& point) const {
        return inverse_ * (point - translation_);
    }

    Vec3 vectorToLocal(const Vec3& vector) const {
        return inverse_ * vector;
    }

    Vec3 pointToWorld(const Vec3& point) const {
        return linear_ * point + translation_;
    }

    Vec3 normalToWorld(const Vec3& normal) const {
        return normalize(inverseTranspose_ * normal);
    }

    float minimumScale() const { return minimumScale_; }

    Transform operator*(const Transform& other) const {
        return Transform(
            linear_ * other.linear_,
            linear_ * other.translation_ + translation_,
            minimumScale_ * other.minimumScale_
        );
    }

private:
    Transform(Mat3 linear, Vec3 translation, float minimumScale)
        : linear_(linear),
          inverse_(linear.inverse()),
          inverseTranspose_(inverse_.transposed()),
          translation_(translation),
          minimumScale_(minimumScale) {}

    Mat3 linear_;
    Mat3 inverse_;
    Mat3 inverseTranspose_;
    Vec3 translation_;
    float minimumScale_ = 1.0f;
};
