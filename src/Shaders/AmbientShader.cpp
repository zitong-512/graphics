#include "Shaders/AmbientShader.hpp"

Vec3 AmbientShader::shade(const Hit&) const {
    return {
        objectColor_.x * ambientLight_.x,
        objectColor_.y * ambientLight_.y,
        objectColor_.z * ambientLight_.z
    };
}
