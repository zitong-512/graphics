#include "Shaders/DiffuseShader.hpp"

Vec3 DiffuseShader::shade(const Hit& hit) const {

    float cos = dot(hit.normal, positionLight_);


    return {
        (cos) * objectColor_.x * ambientLight_.x,
        (cos) * objectColor_.y * ambientLight_.y,
        (cos) * objectColor_.z * ambientLight_.z
    };
}


