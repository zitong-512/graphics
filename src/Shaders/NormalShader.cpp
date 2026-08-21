#include "Shaders/NormalShader.hpp"

Vec3 NormalShader::shade(const Hit& hit) const {
    return {
        hit.normal
    };
}
