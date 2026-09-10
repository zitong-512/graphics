#include "Objects/Cylinder.hpp"

// Cylinder TODOs, roughly in order:
// 1. Give sdf() a real cylinder distance.
// 2. Bail out when the ray is parallel to the cylinder.
// 3. Check the discriminant before taking its square root.
// 4. Calculate both quadratic roots correctly.
// 5. Pick the nearest root that is actually in front of the ray.
// 6. Normalize the hit normal.
// 7. Give the cylinder useful UV coordinates.

float Cylinder::sdf(const Vec3&) const {
    return 0.0f;
}

std::optional<Hit> Cylinder::hit(const Ray& ray, float intersectionEpsilon, float maxDistance) const{
    Vec2 d = planar(ray.direction);
    Vec2 e = planar (ray.origin);
    Vec2 f = planar(center_);

    float a = dot(d, d);
    float b = 2 * dot(d, (e - f));
    float c = dot((e - f), (e - f)) - radius_ * radius_;
    
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0.0f){return std::nullopt;}

    float s = std::sqrt(discriminant);
    float t = std::min(-b + s, -b - s)/ (2 * a);

    if (t < 0.0f){
        float t = std::max(-b + s, -b - s)/ (2 * a);
    }

    const float l = dot(Vec3({0.0f, 0.0f, height_}) - ray.origin, Vec3({0.0f, 0.0f, 1.0f})) / dot(ray.direction, Vec3({0.0f, 0.0f, 1.0f}));
    if (length(ray.at(l) - Vec3({0.0f, 0.0f, height_})) < radius_){
        if (std::min(t, l) > 0){t = std::min(t, l);}
        else{t = std::max(t, l);}
    }

    if (t > 0.0f && t < maxDistance && t > intersectionEpsilon && ray.at(t).z <= height_ && ray.at(t).z >= 0.0f) {
        Hit hit;
        hit.t = t;
        hit.point = ray.at(t); 
        Vec2 normal = planar(hit.point) - planar(center_);
        hit.normal = normalize({normal.x, normal.y, 0.0f});
        hit.uv = {0.0f, 0.0f};
        hit.object = this;

        return hit;
    }
    return std::nullopt;
}



