#include "Shaders/SpecularShader.hpp"

Vec3 SpecularShader::shade(const Hit& hit) const {

    Vec3 l = normalize(positionLight_ - hit.point);
    Vec3 n = normalize(hit.normal);
    Vec3 r = normalize((2 * dot(l, n)) * n - l);
    Vec3 v = normalize(cameraPosition_ - hit.point);

    float cos = dot(r, v) * dot(r, v) * dot(r, v) * dot(r, v) * dot(r, v) * dot(r, v) * dot(r, v)* dot(r, v) * dot(r, v) * dot(r, v) * dot(r, v) * dot(r, v)* dot(r, v) * dot(r, v) * dot(r, v) * dot(r, v)* dot(r, v) * dot(r, v) * dot(r, v) * dot(r, v)* dot(r, v)* dot(r, v) * dot(r, v) * dot(r, v)* dot(r, v)* dot(r, v)* dot(r, v)* dot(r, v)* dot(r, v)* dot(r, v)* dot(r, v)* dot(r, v)* dot(r, v);
    
    if (cos > 0.5) {
        cos = 0.9;
    }
    else {
        cos = 0;
    }
    return {
        cos * ambientLight_.x,
        cos * ambientLight_.y,
        cos * ambientLight_.z
    };
}
