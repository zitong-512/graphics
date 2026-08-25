#include "Scenes/Presets/Primitives/BlinnPhongDonutScene.hpp"

#include "Objects/Donut.hpp"
#include "Scenes/Presets/Primitives/BlinnPhongPrimitiveScene.hpp"
#include "Shaders/BlinnPhongShader.hpp"

#include <memory>
#include <utility>

ScenePreset scenes::blinnPhongDonut::makeScene() {
    constexpr float smallR = 0.3f;
    ObjectPtr donut = std::make_shared<Donut>(
        Vec3{0.0f, 0.0f, smallR},
        1.0f,
        smallR,
        blinnPhongPrimitive::objectMaterial(),
        std::make_shared<BlinnPhongShader>()
    );

    return blinnPhongPrimitive::makeScene(
        std::move(donut),
        "BlinnPhongDonut.ppm"
    );
}

namespace scenes::blinnPhongDonut {
    const ScenePreset preset = makeScene();
}
