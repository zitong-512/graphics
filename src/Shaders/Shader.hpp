#pragma once

#include "Lights/Light.hpp"
#include "Materials/Material.hpp"
#include "Utilities/Camera.hpp"
#include "Utilities/Hit.hpp"

#include <vector>

class Shader {
public:
    virtual ~Shader() = default;
    virtual Vec3 shade(const Hit& hit) const { return hit.normal; }
    virtual Vec3 shade(const Hit& hit,
                       const Material&,
                       const Camera&,
                       const std::vector<LightPtr>&) const {
        return shade(hit);
    }
};
