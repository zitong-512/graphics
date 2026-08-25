#include "Scenes/Presets/Primitives/BlinnPhongCylinderScene.hpp"

#include "Objects/Cylinder.hpp"
#include "Scenes/Presets/Primitives/BlinnPhongPrimitiveScene.hpp"
#include "Shaders/BlinnPhongShader.hpp"

#include <memory>
#include <utility>

ScenePreset scenes::blinnPhongCylinder::makeScene() {
    constexpr float height = 1.5f;
    ObjectPtr cylinder = std::make_shared<Cylinder>(
        Vec3{0.0f, 0.0f, height * 0.5f},
        0.75f,
        height,
        blinnPhongPrimitive::objectMaterial(),
        std::make_shared<BlinnPhongShader>()
    );

    return blinnPhongPrimitive::makeScene(
        std::move(cylinder),
        "BlinnPhongCylinder.ppm"
    );
}

namespace scenes::blinnPhongCylinder {
    const ScenePreset preset = makeScene();
}
