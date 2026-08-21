#include "Shaders/ToonShader.hpp"
#include "Shaders/AmbientShader.hpp"
#include "Shaders/DiffuseToonShader.hpp"
#include "Shaders/SpecularToonShader.hpp"

Vec3 ToonShader::shade(const Hit& hit) const {
    AmbientShader ambient;
    DiffuseToonShader diffuse;
    SpecularToonShader specular;

    Vec3 shade = specular.shade(hit) + ambient.shade(hit) + diffuse.shade(hit);

    return {
        shade
    };

}
