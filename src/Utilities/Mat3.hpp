#pragma once

#include "Utilities/Vec3.hpp"

#include <cmath>
#include <stdexcept>

struct Mat3 {
    float values[3][3] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    constexpr Mat3() = default;

    constexpr Mat3(float m00, float m01, float m02,
                   float m10, float m11, float m12,
                   float m20, float m21, float m22)
        : values{{m00, m01, m02},
                 {m10, m11, m12},
                 {m20, m21, m22}} {}

    static constexpr Mat3 identity() { return {}; }

    static constexpr Mat3 scale(const Vec3& scale) {
        return {
            scale.x, 0.0f, 0.0f,
            0.0f, scale.y, 0.0f,
            0.0f, 0.0f, scale.z
        };
    }

    static Mat3 rotationX(float angle) {
        const float cosine = std::cos(angle);
        const float sine = std::sin(angle);
        return {
            1.0f, 0.0f, 0.0f,
            0.0f, cosine, -sine,
            0.0f, sine, cosine
        };
    }

    static Mat3 rotationY(float angle) {
        const float cosine = std::cos(angle);
        const float sine = std::sin(angle);
        return {
            cosine, 0.0f, sine,
            0.0f, 1.0f, 0.0f,
            -sine, 0.0f, cosine
        };
    }

    static Mat3 rotationZ(float angle) {
        const float cosine = std::cos(angle);
        const float sine = std::sin(angle);
        return {
            cosine, -sine, 0.0f,
            sine, cosine, 0.0f,
            0.0f, 0.0f, 1.0f
        };
    }

    constexpr Vec3 operator*(const Vec3& vector) const {
        return {
            values[0][0] * vector.x + values[0][1] * vector.y
                + values[0][2] * vector.z,
            values[1][0] * vector.x + values[1][1] * vector.y
                + values[1][2] * vector.z,
            values[2][0] * vector.x + values[2][1] * vector.y
                + values[2][2] * vector.z
        };
    }

    constexpr Mat3 operator*(const Mat3& other) const {
        Mat3 result{
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f
        };
        for (int row = 0; row < 3; ++row) {
            for (int column = 0; column < 3; ++column) {
                for (int index = 0; index < 3; ++index) {
                    result.values[row][column] +=
                        values[row][index] * other.values[index][column];
                }
            }
        }
        return result;
    }

    constexpr Mat3 transposed() const {
        return {
            values[0][0], values[1][0], values[2][0],
            values[0][1], values[1][1], values[2][1],
            values[0][2], values[1][2], values[2][2]
        };
    }

    constexpr float determinant() const {
        return values[0][0]
                * (values[1][1] * values[2][2]
                   - values[1][2] * values[2][1])
            - values[0][1]
                * (values[1][0] * values[2][2]
                   - values[1][2] * values[2][0])
            + values[0][2]
                * (values[1][0] * values[2][1]
                   - values[1][1] * values[2][0]);
    }

    Mat3 inverse() const {
        const float determinantValue = determinant();
        constexpr float epsilon = 1.0e-8f;
        if (std::abs(determinantValue) <= epsilon) {
            throw std::invalid_argument("Transform matrix must be invertible");
        }

        const float inverseDeterminant = 1.0f / determinantValue;
        return Mat3{
            values[1][1] * values[2][2] - values[1][2] * values[2][1],
            values[0][2] * values[2][1] - values[0][1] * values[2][2],
            values[0][1] * values[1][2] - values[0][2] * values[1][1],
            values[1][2] * values[2][0] - values[1][0] * values[2][2],
            values[0][0] * values[2][2] - values[0][2] * values[2][0],
            values[0][2] * values[1][0] - values[0][0] * values[1][2],
            values[1][0] * values[2][1] - values[1][1] * values[2][0],
            values[0][1] * values[2][0] - values[0][0] * values[2][1],
            values[0][0] * values[1][1] - values[0][1] * values[1][0]
        } * inverseDeterminant;
    }

    constexpr Mat3 operator*(float scalar) const {
        return {
            values[0][0] * scalar, values[0][1] * scalar,
            values[0][2] * scalar, values[1][0] * scalar,
            values[1][1] * scalar, values[1][2] * scalar,
            values[2][0] * scalar, values[2][1] * scalar,
            values[2][2] * scalar
        };
    }

    float frobeniusNorm() const {
        float sum = 0.0f;
        for (const auto& row : values) {
            for (float value : row) {
                sum += value * value;
            }
        }
        return std::sqrt(sum);
    }
};
