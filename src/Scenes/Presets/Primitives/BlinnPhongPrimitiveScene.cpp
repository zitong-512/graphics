#include "Scenes/Presets/Primitives/BlinnPhongPrimitiveScene.hpp"

#include "Lights/AmbientLight.hpp"
#include "Lights/PointLight.hpp"
#include "Objects/Plane.hpp"
#include "Shaders/BlinnPhongShader.hpp"
#include "Textures/CheckerboardTexture.hpp"

#include <memory>
#include <utility>
#include <vector>

Material scenes::blinnPhongPrimitive::objectMaterial() {
    return {
        {0.3f, 0.6f, 0.9f},
        {1.0f, 1.0f, 1.0f},
        32.0f
    };
}

ScenePreset scenes::blinnPhongPrimitive::makeScene(
    ObjectPtr object,
    const std::filesystem::path& outputFilename
) {
    Camera camera{
        {1.0f, -2.0f, 2.5f}, // Position
        {0.0f, 1.0f, 0.0f},  // Target
        {0.0f, 0.0f, 1.0f},  // Up
        8.0f / 3.0f,         // Viewport width
        2.0f                 // Viewport height
    };

    const Vec3 background{0.05f, 0.07f, 0.12f};
    std::vector<LightPtr> lights{
        std::make_shared<AmbientLight>(Vec3{0.08f, 0.08f, 0.08f}),
        std::make_shared<PointLight>(
            Vec3{-2.0f, -2.0f, 3.0f},
            Vec3{0.9f, 0.9f, 0.9f}
        ),
        std::make_shared<PointLight>(
            Vec3{1.0f, -1.0f, 0.5f},
            Vec3{0.1f, 0.1f, 0.3f}
        )
    };

    const Material planeMaterial{
        {0.1f, 0.1f, 0.1f}, // Diffuse color
        {0.9f, 0.9f, 0.9f},
        16.0f,
        std::make_shared<CheckerboardTexture>(
            Vec3{0.0f, 0.0f, 0.0f},
            Vec3{0.85f, 0.85f, 0.85f},
            1.0f
        )
    };
    ObjectPtr plane = std::make_shared<Plane>(
        Vec3{5.0f, 0.0f, 0.0f},
        Vec3{0.0f, 0.0f, 1.0f},
        planeMaterial,
        std::make_shared<BlinnPhongShader>(),
        Vec3{1.0f, 0.0f, 0.0f},
        Vec3{0.0f, 1.0f, 0.0f}
    );

    std::vector<ObjectPtr> objects{
        std::move(object),
        std::move(plane)
    };

    return ScenePreset{
        Scene{
            std::move(camera),
            background,
            std::move(lights),
            std::move(objects)
        },
        std::filesystem::path{GRAPHICS_RENDER_DIR}
            / "Primitives"
            / outputFilename
    };
}
