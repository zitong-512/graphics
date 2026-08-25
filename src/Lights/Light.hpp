#pragma once

#include "Utilities/Vec3.hpp"

#include <memory>

class Light {
public:
    virtual ~Light() = default;

    const Vec3& color() const { return color_; }

protected:
    explicit Light(Vec3 color) : color_(color) {}

private:
    Vec3 color_;
};

using LightPtr = std::shared_ptr<const Light>;