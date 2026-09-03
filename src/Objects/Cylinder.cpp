#include "Objects/Cylinder.hpp"

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

    float s = std::sqrt(b * b - 4 * a * c);
    float t = std::min(-b + s, - - s) / (2 * a);



    if (s >= 0 && t < maxDistance && t > intersectionEpsilon) {
        Hit hit;
        hit.t = t;
        hit.point = ray.at(t);
        Vec2 normal = planar(hit.point) - planar(center_);
        hit.normal = {normal.x, normal.y, 0.0f};
        hit.uv = {0.0f, 0.0f};
        hit.object = this;

        return hit;
    }
    else {
        return std::nullopt;
    }

}



