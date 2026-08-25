#include "Scenes/Presets/Primitives/BlinnPhongTetrahedronScene.hpp"

#include "Objects/Tetrahedron.hpp"
#include "Scenes/Presets/Primitives/BlinnPhongPrimitiveScene.hpp"
#include "Shaders/BlinnPhongShader.hpp"

#include <memory>
#include <utility>

ScenePreset scenes::blinnPhongTetrahedron::makeScene() {
    constexpr float radius = 0.25;
    ObjectPtr tetrahedron = std::make_shared<Tetrahedron>(
        Vec3{0.0f, 0.0f, 1.0f},
        radius,
        blinnPhongPrimitive::objectMaterial(),
        std::make_shared<BlinnPhongShader>()
    );

    return blinnPhongPrimitive::makeScene(
        std::move(tetrahedron),
        "BlinnPhongTetrahedron.ppm"
    );
}

namespace scenes::blinnPhongTetrahedron {
    const ScenePreset preset = makeScene();
}
