#include "Scenes/Presets/Primitives/BlinnPhongIcosahedronScene.hpp"

#include "Objects/Icosahedron.hpp"
#include "Scenes/Presets/Primitives/BlinnPhongPrimitiveScene.hpp"
#include "Shaders/BlinnPhongShader.hpp"

#include <memory>
#include <utility>

ScenePreset scenes::blinnPhongIcosahedron::makeScene() {
    // This inradius gives the current orientation a vertical half-extent of 1.
    constexpr float radius = 0.93417235896f;
    ObjectPtr icosahedron = std::make_shared<Icosahedron>(
        Vec3{0.0f, 0.0f, 1.0f},
        radius,
        blinnPhongPrimitive::objectMaterial(),
        std::make_shared<BlinnPhongShader>()
    );

    return blinnPhongPrimitive::makeScene(
        std::move(icosahedron),
        "BlinnPhongIcosahedron.ppm"
    );
}

namespace scenes::blinnPhongIcosahedron {
    const ScenePreset preset = makeScene();
}
