#include "Scenes/Presets/BlinnPhongPlaneScene.hpp"

#include "Lights/AmbientLight.hpp"
#include "Lights/PointLight.hpp"
#include "Materials/Material.hpp"
#include "Objects/Plane.hpp"
#include "Shaders/BlinnPhongShader.hpp"

#include <memory>
#include <utility>
#include <vector>

ScenePreset scenes::blinnPhongPlane::makeScene() {
    Camera camera{
        {0.0f, 0.0f, 0.0f},  // Position
        {0.0f, 0.0f, -1.0f}, // Target
        {0.0f, 1.0f, 0.0f},  // Up
        8.0f / 3.0f,         // Viewport width
        2.0f                 // Viewport height
    };

    const Vec3 background{0.05f, 0.07f, 0.12f};
    std::vector<LightPtr> lights{
        std::make_shared<AmbientLight>(Vec3{0.08f, 0.08f, 0.08f}),
        std::make_shared<PointLight>(
            Vec3{-2.0f, 3.0f, 0.0f},
            Vec3{0.9f, 0.9f, 0.9f}
        ),
        std::make_shared<PointLight>(
            Vec3{2.0f, 1.0f, -1.0f},
            Vec3{0.2f, 0.25f, 0.35f}
        )
    };

    const Material material{
        {0.4f, 0.4f, 0.85f},
        {1.0f, 1.0f, 1.0f},
        32.0f
    };
    auto shader = std::make_shared<BlinnPhongShader>();

    ObjectPtr plane = std::make_shared<Plane>(
        Vec3{0.0f, 0.0f, -3.0f}, // Point
        Vec3{0.0f, 0.0f, 1.0f}, // Normal,
        material,
        std::move(shader)
    );
    std::vector<ObjectPtr> objects{std::move(plane)};

    return ScenePreset{
        Scene{
            std::move(camera),
            background,
            std::move(lights),
            std::move(objects)
        },
        std::filesystem::path{GRAPHICS_RENDER_DIR} / "BlinnPhongPlane.ppm"
    };
}

namespace scenes::blinnPhongPlane {
    const ScenePreset preset = makeScene();
}