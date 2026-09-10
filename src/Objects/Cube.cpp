#include "Objects/Cube.hpp"

float Cube::sdf(const Vec3& point) const {
    Vec3 q(std::abs(point.x - center_.x) - radius_, std::abs(point.y - center_.y) - radius_, std::abs(point.z - center_.z) - radius_);

    float x = std::max(q.x, 0.0f);
    float y = std::max(q.y, 0.0f);
    float z = std::max(q.z, 0.0f);

    float outside = std::sqrt(x * x + y * y + z * z);
    float inside = std::min(std::max(q.x, std::max(q.y, q.z)), 0.0f);

    return outside + inside;
}
std::optional<Hit> Cube::hit(const Ray& ray, float intersectionEpsilon, float maxDistance) const{
    float ty = std::min((radius_ + center_.y - ray.origin.y) / ray.direction.y, (- radius_ + center_.y - ray.origin.y) / ray.direction.y);
    if (ty < 0){
        float ty = std::max((radius_ + center_.y - ray.origin.y) / ray.direction.y, (- radius_ + center_.y - ray.origin.y) / ray.direction.y);
    }
    float tx = std::min((radius_ + center_.x - ray.origin.x) / ray.direction.x, (- radius_ + center_.x - ray.origin.x) / ray.direction.x);
    if (tx < 0){
        float tx = std::max((radius_ + center_.x - ray.origin.x) / ray.direction.x, (- radius_ + center_.x - ray.origin.x) / ray.direction.x);
    }

    float t = std::min(ty, tx);
    if (t < 0){t = std::max(ty, tx);}

    if (t > 0.0f && t < maxDistance && t > intersectionEpsilon  ) {
        if ((t == ty && center_.x - radius_ < ray.at(t).x && ray.at(t).x < center_.x + radius_ && ray.at(t).z < center_.z + radius_)
    || (t == tx && center_.y - radius_ < ray.at(t).y && ray.at(t).y < center_.y + radius_ && ray.at(t).z < center_.z + radius_)){
        Hit hit;
        hit.t = t;
        hit.point = ray.at(t); 
        if (t == ty){hit.normal = Vec3({0.0f, -1.0f, 0.0f});}
        if (t == tx){hit.normal = Vec3({-1.0f, 0.0f, 0.0f});}
        hit.uv = {0.0f, 0.0f};
        hit.object = this;

        return hit;
        }
    return std::nullopt;
    }
}

 
 