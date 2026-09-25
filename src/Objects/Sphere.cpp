#include "Objects/Sphere.hpp"

#include <cmath>

namespace {
constexpr float pi = 3.14159265358979323846f;

Vec3 rotateAroundX(const Vec3& vector, float angle) {
    const float cosine = std::cos(angle);
    const float sine = std::sin(angle);
    return {
        vector.x,
        cosine * vector.y - sine * vector.z,
        sine * vector.y + cosine * vector.z
    };
}

Vec3 rotateAroundY(const Vec3& vector, float angle) {
    const float cosine = std::cos(angle);
    const float sine = std::sin(angle);
    return {
        cosine * vector.x + sine * vector.z,
        vector.y,
        -sine * vector.x + cosine * vector.z
    };
}

Vec3 rotateAroundZ(const Vec3& vector, float angle) {
    const float cosine = std::cos(angle);
    const float sine = std::sin(angle);
    return {
        cosine * vector.x - sine * vector.y,
        sine * vector.x + cosine * vector.y,
        vector.z
    };
}

Vec3 inverseRotate(const Vec3& vector, const Vec3& orientation) {
    Vec3 result = rotateAroundZ(vector, -orientation.z);
    result = rotateAroundY(result, -orientation.y);
    return rotateAroundX(result, -orientation.x);
}
}

float Sphere::sdf(const Vec3& point) const {
    return length(point - center_) - radius_;
}

Vec3 Sphere::normal(const Vec3& point) const {
    return normalize(point - center_);
}

Vec2 Sphere::textureCoordinates(const Vec3& point) const {
    const Vec3 worldDirection = normalize(point - center_);
    const Vec3 direction = inverseRotate(worldDirection, orientation_);
    return {
        0.5f + std::atan2(direction.z, direction.x) / (2.0f * pi),
        0.5f - std::asin(direction.y) / pi
    };
}

std::optional<Hit> Sphere::hit(const Ray& ray,
                                float intersectionEpsilon,
                                float maxDistance) const {
    
    float a = dot(ray.direction, ray.direction);
    float b = dot(2 * ray.direction, ray.origin - center_);
    float c = dot(ray.origin - center_, ray.origin - center_) - radius_ * radius_; 

    float d = std::sqrt(b*b - 4*a*c);
    float t = std::min(-b + d, -b - d) / (2 * a);

    if (t < 0.0f) {
        t = std::max(-b + d, -b - d) / (2 * a);
    }

    if (d >= 0 && t > 0.0f && t < maxDistance && t > intersectionEpsilon) {
        Hit hit;
        hit.t = t;
        hit.point = ray.origin + hit.t * ray.direction;
        hit.normal = Sphere::normal(hit.point);
        hit.uv = textureCoordinates(hit.point);
        hit.object = this;

        return hit;
    }
    else {
        return std::nullopt;
    }
}

/* 
struct Hit {
    float t = 0.0f;
    Vec3 point;
    Vec3 normal;
    Vec2 uv;
    const Object* object = nullptr;
};
*/
