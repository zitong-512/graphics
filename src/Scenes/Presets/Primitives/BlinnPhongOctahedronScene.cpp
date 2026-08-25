#include "Scenes/Presets/Primitives/BlinnPhongOctahedronScene.hpp"

#include "Objects/Octahedron.hpp"
#include "Scenes/Presets/Primitives/BlinnPhongPrimitiveScene.hpp"
#include "Shaders/BlinnPhongShader.hpp"

#include <memory>
#include <utility>

ScenePreset scenes::blinnPhongOctahedron::makeScene() {
    // An inradius of 1 / sqrt(3) gives a vertical half-extent of 1.
    constexpr float radius = 0.57735026919f;
    ObjectPtr octahedron = std::make_shared<Octahedron>(
        Vec3{0.0f, 0.0f, 1.0f},
        radius,
        blinnPhongPrimitive::objectMaterial(),
        std::make_shared<BlinnPhongShader>()
    );

    return blinnPhongPrimitive::makeScene(
        std::move(octahedron),
        "BlinnPhongOctahedron.ppm"
    );
}

namespace scenes::blinnPhongOctahedron {
    const ScenePreset preset = makeScene();
}
