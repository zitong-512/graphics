#include "Objects/Sphere.hpp"

float Sphere::sdf(const Vec3& point) const {
    return length(point - center_) - radius_;
}

Vec3 Sphere::normal(const Vec3& point) const {
    return normalize(point - center_);
}

std::optional<Hit> Sphere::hit(const Ray& ray,
                                float intersectionEpsilon,
                                float maxDistance) const {
    
    float a = dot(ray.direction, ray.direction);
    float b = dot(2 * ray.direction, ray.origin - center_);
    float c = dot(ray.origin - center_, ray.origin - center_) - radius_ * radius_; 

    float d = std::sqrt(b*b - 4*a*c);

    if (d >= 0){
        float t1 = (-b + d) / (2 * a);
        float t2 = (-b - d) / (2 * a);

        Hit hit;
        hit.t = std::min(t1, t2);
        hit.point = ray.origin + hit.t * ray.direction;
        hit.normal = Sphere::normal(hit.point);
        hit.uv = {0.0f, 0.0f};
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