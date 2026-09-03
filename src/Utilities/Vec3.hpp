#pragma once

#include <cmath>
#include "Utilities/Vec2.hpp"

struct Vec3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    constexpr Vec3() = default;
    constexpr Vec3(float xValue, float yValue, float zValue)
        : x(xValue), y(yValue), z(zValue) {}

    constexpr Vec3 operator-() const { return {-x, -y, -z}; }
    constexpr Vec3 operator+(const Vec3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }
    constexpr Vec3 operator-(const Vec3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
    constexpr Vec3 operator*(float scalar) const {
        return {x * scalar, y * scalar, z * scalar};
    }
    constexpr Vec3 operator/(float scalar) const {
        return *this * (1.0f / scalar);
    }
};



inline constexpr Vec3 operator*(float scalar, const Vec3& vector) {
    return vector * scalar;
}

inline constexpr float dot(const Vec3& a, const Vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline constexpr Vec3 cross(const Vec3& a, const Vec3& b) {
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

inline float length(const Vec3& vector) {
    return std::sqrt(dot(vector, vector));
}

inline Vec3 normalize(const Vec3& vector) {
    return vector / length(vector);
}

inline Vec2 planar(const Vec3& vector) {
    return {vector.x, vector.y};
}