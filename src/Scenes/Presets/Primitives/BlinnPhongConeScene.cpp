#include "Scenes/Presets/Primitives/BlinnPhongConeScene.hpp"

#include "Objects/Cone.hpp"
#include "Scenes/Presets/Primitives/BlinnPhongPrimitiveScene.hpp"
#include "Shaders/BlinnPhongShader.hpp"

#include <memory>
#include <utility>

ScenePreset scenes::blinnPhongCone::makeScene() {
    constexpr float height = 2.0f;
    ObjectPtr cone = std::make_shared<Cone>(
        Vec3{0.0f, 0.0f, height * 0.5f},
        1.0f,
        height,
        blinnPhongPrimitive::objectMaterial(),
        std::make_shared<BlinnPhongShader>()
    );

    return blinnPhongPrimitive::makeScene(
        std::move(cone),
        "BlinnPhongCone.ppm"
    );
}

namespace scenes::blinnPhongCone {
    const ScenePreset preset = makeScene();
}
