#include "Shaders/DiffuseToonShader.hpp"

Vec3 DiffuseToonShader::shade(const Hit& hit) const {

    float cos = dot(hit.normal, positionLight_);

    if (cos > 0.3 and cos < 0.8) {
        cos = 0.5;
    }
    else if (cos >= 0.8) {
        cos = 0.7;
    }
    else {
        cos = 0.2;
    }
    return {
        (cos) * objectColor_.x * ambientLight_.x,
        (cos) * objectColor_.y * ambientLight_.y,
        (cos) * objectColor_.z * ambientLight_.z
    };
}


