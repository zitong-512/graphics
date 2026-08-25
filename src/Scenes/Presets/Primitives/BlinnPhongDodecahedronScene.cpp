#include "Scenes/Presets/Primitives/BlinnPhongDodecahedronScene.hpp"

#include "Objects/Dodecahedron.hpp"
#include "Scenes/Presets/Primitives/BlinnPhongPrimitiveScene.hpp"
#include "Shaders/BlinnPhongShader.hpp"

#include <memory>
#include <utility>

ScenePreset scenes::blinnPhongDodecahedron::makeScene() {
    // This inradius gives the current orientation a vertical half-extent of 1.
    constexpr float radius = 0.85065080835f;
    ObjectPtr dodecahedron = std::make_shared<Dodecahedron>(
        Vec3{0.0f, 0.0f, 1.0f},
        radius,
        blinnPhongPrimitive::objectMaterial(),
        std::make_shared<BlinnPhongShader>()
    );

    return blinnPhongPrimitive::makeScene(
        std::move(dodecahedron),
        "BlinnPhongDodecahedron.ppm"
    );
}

namespace scenes::blinnPhongDodecahedron {
    const ScenePreset preset = makeScene();
}
