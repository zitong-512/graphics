#include "Shaders/BlinnPhong.hpp"
#include "Shaders/AmbientShader.hpp"
#include "Shaders/DiffuseShader.hpp"
#include "Shaders/SpecularShader.hpp"

Vec3 BlinnPhong::shade(const Hit& hit) const {
    AmbientShader ambient;
    DiffuseShader diffuse;
    SpecularShader specular;

    Vec3 shade = specular.shade(hit) + ambient.shade(hit) + diffuse.shade(hit);

    return {
        shade
    };

}
