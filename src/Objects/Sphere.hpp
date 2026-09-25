#pragma once

#include "Objects/Object.hpp"

#include <utility>

class Sphere final : public Object {
public:
    // Orientation contains X, Y, and Z Euler angles in radians. The rotations
    // are applied in that order when orienting the sphere's texture.
    Sphere(Vec3 center,
           float radius,
           Material material,
           std::shared_ptr<const Shader> shader,
           Vec3 orientation = {})
        : Object(std::move(material), std::move(shader)),
          center_(center),
          radius_(radius),
          orientation_(orientation) {}

    float sdf(const Vec3& point) const override;
    Vec3 normal(const Vec3& point) const override;
    Vec2 textureCoordinates(const Vec3& point) const override;
    std::optional<Hit> hit(const Ray& ray,
                           float intersectionEpsilon,
                           float maxDistance) const override;

    const Vec3& getCenter() const { return center_; }
    void setCenter(Vec3 center) { center_ = center; }

    const float getRadius() const {return radius_; }
    void setRadius(float radius) { radius_ = radius; } 

    const Vec3& getOrientation() const { return orientation_; }
    void setOrientation(Vec3 orientation) { orientation_ = orientation; }

private:
    Vec3 center_;
    float radius_;
    Vec3 orientation_;
};
