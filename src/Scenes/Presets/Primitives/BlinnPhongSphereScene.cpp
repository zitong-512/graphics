#include "Scenes/Presets/Primitives/BlinnPhongSphereScene.hpp"

#include "Objects/Sphere.hpp"
#include "Scenes/Presets/Primitives/BlinnPhongPrimitiveScene.hpp"
#include "Shaders/BlinnPhongShader.hpp"

#include <memory>
#include <utility>

ScenePreset scenes::blinnPhongSphere::makeScene() {
    constexpr float radius = 1.0f;
    ObjectPtr sphere = std::make_shared<Sphere>(
        Vec3{0.0f, 0.0f, radius},
        radius,
        blinnPhongPrimitive::objectMaterial(),
        std::make_shared<BlinnPhongShader>()
    );


    return blinnPhongPrimitive::makeScene(
        std::move(sphere),
        "BlinnPhongSphere.ppm"
    );
}

namespace scenes::blinnPhongSphere {
    const ScenePreset preset = makeScene();
}
