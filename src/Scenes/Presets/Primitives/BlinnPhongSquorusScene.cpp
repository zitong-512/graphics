#include "Scenes/Presets/Primitives/BlinnPhongSquorusScene.hpp"

#include "Objects/Squorus.hpp"
#include "Scenes/Presets/Primitives/BlinnPhongPrimitiveScene.hpp"
#include "Shaders/BlinnPhongShader.hpp"

#include <memory>
#include <utility>

ScenePreset scenes::blinnPhongSquorus::makeScene() {
    constexpr float smallR = 0.3f;
    ObjectPtr squorus = std::make_shared<Squorus>(
        Vec3{0.0f, 0.0f, smallR},
        1.0f,
        smallR,
        blinnPhongPrimitive::objectMaterial(),
        std::make_shared<BlinnPhongShader>()
    );

    return blinnPhongPrimitive::makeScene(
        std::move(squorus),
        "BlinnPhongSquorus.ppm"
    );
}

namespace scenes::blinnPhongSquorus {
    const ScenePreset preset = makeScene();
}
