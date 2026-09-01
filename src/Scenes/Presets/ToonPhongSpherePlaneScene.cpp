#include "Scenes/Presets/ToonPhongSpherePlaneScene.hpp"

#include "Lights/AmbientLight.hpp"
#include "Lights/PointLight.hpp"
#include "Materials/Material.hpp"
#include "Objects/Plane.hpp"
#include "Objects/Sphere.hpp"
#include "Shaders/BlinnPhongShader.hpp"
#include "Shaders/ToonShader.hpp"

#include <memory>
#include <utility>
#include <vector>

ScenePreset scenes::toonPhongSpherePlane::makeScene() {
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
            Vec3{-2.0f, 1.0f, -1.0f}, // Position
            Vec3{0.9f, 0.9f, 0.9f}   // Color
        )
    };

    const Material toonMaterial{
        {0.4f, 0.4f, 0.85f},
        {1.0f, 1.0f, 1.0f},
        32.0f
    };
    auto toonShader = std::make_shared<ToonShader>(
        Vec3{0.0f, 0.0f, 0.0f},
        Vec3{0.0f, 0.0f, 0.0f}
    );
    ObjectPtr toonSphere = std::make_shared<Sphere>(
        Vec3{-1.05f, 0.0f, -3.0f},
        1.0f,
        toonMaterial,
        std::move(toonShader)
    );

    const Material blinnPhongMaterial{
        {0.4f, 0.4f, 0.85f},
        {1.0f, 1.0f, 1.0f},
        32.0f
    };
    auto blinnPhongShader = std::make_shared<BlinnPhongShader>();
    ObjectPtr blinnPhongSphere = std::make_shared<Sphere>(
        Vec3{1.05f, 0.0f, -3.0f},
        1.0f,
        blinnPhongMaterial,
        blinnPhongShader
    );

    const Material planeMaterial{
        {0.3f, 0.32f, 0.36f},
        {1.0f, 1.0f, 1.0f},
        16.0f
    };
    ObjectPtr plane = std::make_shared<Plane>(
        Vec3{0.0f, -1.0f, 0.0f},
        Vec3{0.0f, 1.0f, 0.0f},
        planeMaterial,
        std::move(blinnPhongShader)
    );

    std::vector<ObjectPtr> objects{
        std::move(toonSphere),
        std::move(blinnPhongSphere),
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
            / "ToonPhongSpherePlane.ppm"
    };
}

namespace scenes::toonPhongSpherePlane {
    const ScenePreset preset = makeScene();
}
