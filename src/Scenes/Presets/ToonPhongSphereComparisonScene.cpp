#include "Scenes/Presets/ToonPhongSphereComparisonScene.hpp"

#include "Lights/AmbientLight.hpp"
#include "Lights/PointLight.hpp"
#include "Materials/Material.hpp"
#include "Objects/Sphere.hpp"
#include "Shaders/BlinnPhongShader.hpp"
#include "Shaders/ToonShader.hpp"

#include <memory>
#include <utility>
#include <vector>

ScenePreset scenes::toonPhongSphereComparison::makeScene() {
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

    /* Toon Sphere */
    const Material toonMaterial{
        {0.4f, 0.4f, 0.85f},
        {1.0f, 1.0f, 1.0f},
        32.0f
    };
    auto toonShader = std::make_shared<ToonShader>({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});
    ObjectPtr toonSphere = std::make_shared<Sphere>(
        Vec3{-1.05f, 0.0f, -3.0f}, // Position
        1.0f, // Radius
        toonMaterial,
        std::move(toonShader)
    );

    /* BlinnPhong Sphere */
    const Material blinnPhongMaterial{
        {0.4f, 0.4f, 0.85f},
        {1.0f, 1.0f, 1.0f},
        32.0f
    };
    auto blinnPhongShader = std::make_shared<BlinnPhongShader>();
    ObjectPtr blinnPhongSphere = std::make_shared<Sphere>(
        Vec3{1.05f, 0.0f, -3.0f}, // Position
        1.0f, // Radius
        blinnPhongMaterial,
        std::move(blinnPhongShader)
    );

    std::vector<ObjectPtr> objects{
        std::move(toonSphere),
        std::move(blinnPhongSphere)
    };

    return ScenePreset{
        Scene{
            std::move(camera),
            background,
            std::move(lights),
            std::move(objects)
        },
        std::filesystem::path{GRAPHICS_RENDER_DIR}
            / "ToonPhongSphereComparison.ppm"
    };
}

namespace scenes::toonPhongSphereComparison {
    const ScenePreset preset = makeScene();
}
