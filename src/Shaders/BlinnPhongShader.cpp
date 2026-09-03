#include "Shaders/BlinnPhongShader.hpp"

#include "Lights/AmbientLight.hpp"
#include "Lights/PointLight.hpp"

#include <algorithm>
#include <cmath>

namespace {
Vec3 multiply(const Vec3& left, const Vec3& right) {
    return {left.x * right.x, left.y * right.y, left.z * right.z};
}
} 

Vec3 BlinnPhongShader::shade( 
    const Hit& hit,
    const Material& material,
    const Camera& camera,
    const std::vector<LightPtr>& lights
) const {
    const Vec3 objectColor = material.colorAt(hit.uv);
    Vec3 result{};
    const Vec3 viewDirection = normalize(camera.position() - hit.point);

    for (const LightPtr& light : lights) {
        if (dynamic_cast<const AmbientLight*>(light.get()) != nullptr) {
            result = result + multiply(objectColor, light->color());
            continue;
        }

        const auto* pointLight = dynamic_cast<const PointLight*>(light.get());
        if (pointLight == nullptr) {
            continue;
        }

        const Vec3 lightDirection = normalize(pointLight->position() - hit.point);
        const float diffuse = std::max(dot(hit.normal, lightDirection), 0.0f);
        result = result + diffuse * multiply(objectColor, pointLight->color());

        if (diffuse > 0.0f) {
            const Vec3 halfway = normalize(lightDirection + viewDirection);
            const float specular = std::pow(
                std::max(dot(hit.normal, halfway), 0.0f),
                material.shininess
            );
            result = result
                + specular * multiply(material.specularColor, pointLight->color());
        }
    }

    return result;
}
