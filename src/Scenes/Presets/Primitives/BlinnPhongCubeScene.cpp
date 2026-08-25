#include "Scenes/Presets/Primitives/BlinnPhongCubeScene.hpp"

#include "Objects/Cube.hpp"
#include "Scenes/Presets/Primitives/BlinnPhongPrimitiveScene.hpp"
#include "Shaders/BlinnPhongShader.hpp"

#include <memory>
#include <utility>

ScenePreset scenes::blinnPhongCube::makeScene() {
    constexpr float radius = 0.75f;
    ObjectPtr cube = std::make_shared<Cube>(
        Vec3{0.0f, 0.0f, radius},
        radius,
        blinnPhongPrimitive::objectMaterial(),
        std::make_shared<BlinnPhongShader>()
    );

    return blinnPhongPrimitive::makeScene(
        std::move(cube),
        "BlinnPhongCube.ppm"
    );
}

namespace scenes::blinnPhongCube {
    const ScenePreset preset = makeScene();
}
