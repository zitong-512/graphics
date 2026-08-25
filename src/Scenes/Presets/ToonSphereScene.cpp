#include "Scenes/Presets/ToonSphereScene.hpp"

#include "Lights/AmbientLight.hpp"
#include "Lights/PointLight.hpp"
#include "Materials/Material.hpp"
#include "Objects/Sphere.hpp"
#include "Shaders/ToonShader.hpp"

#include <memory>
#include <utility>
#include <vector>

ScenePreset scenes::toonSphere::makeScene() {
    Camera camera{
        {0.0f, 0.0f, 0.0f},  // Position
        {0.0f, 0.0f, -1.0f}, // Target
        {0.0f, 1.0f, 0.0f},  // Up
        8.0f / 3.0f,         // Viewport width
        2.0f                 // Viewport height
    };

    const Vec3 background{0.05f, 0.07f, 0.12f};
    std::vector<LightPtr> lights{
        std::make_shared<AmbientLight>(Vec3{0.8f, 0.8f, 0.8f}),
        std::make_shared<PointLight>(
            Vec3{-2.0f, 3.0f, 0.0f},
            Vec3{0.9f, 0.9f, 0.9f}
        )
    };

    const Material material{
        {0.4f, 0.4f, 0.85f},
        {1.0f, 1.0f, 1.0f},
        32.0f
    };
    auto shader = std::make_shared<ToonShader>(3);

    ObjectPtr sphere = std::make_shared<Sphere>(
        Vec3{0.0f, 0.0f, -3.0f}, // Position
        1.0f, // Radius
        material,
        std::move(shader)
    );
    std::vector<ObjectPtr> objects{std::move(sphere)};

    return ScenePreset{
        Scene{
            std::move(camera),
            background,
            std::move(lights),
            std::move(objects)
        },
        std::filesystem::path{GRAPHICS_RENDER_DIR} / "ToonSphere.ppm"
    };
}

namespace scenes::toonSphere {
    const ScenePreset preset = makeScene();
}
