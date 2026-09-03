#pragma once

struct Vec2 {
    float x = 0.0f;
    float y = 0.0f;

    constexpr Vec2() = default;
    constexpr Vec2(float xValue, float yValue)
        : x(xValue), y(yValue) {}

    constexpr Vec2 operator-(const Vec2& other) const {
        return {x - other.x, y - other.y} ;
    }

    constexpr Vec2 operator*(const float& scalar) const {
        return {scalar * x, scalar * y} ;
    }
};

float dot(const Vec2& a , const Vec2& b){
    return a.x * b.x + a.y * b.y;

}

