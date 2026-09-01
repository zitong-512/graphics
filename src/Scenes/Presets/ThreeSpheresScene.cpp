#include "Scenes/Presets/ThreeSpheresScene.hpp"

#include "Lights/AmbientLight.hpp"
#include "Lights/PointLight.hpp"
#include "Materials/Material.hpp"
#include "Objects/Plane.hpp"
#include "Objects/Sphere.hpp"
#include "Shaders/AmbientShader.hpp"
#include "Shaders/BlinnPhongShader.hpp"
#include "Shaders/ToonShader.hpp"
#include "Textures/CheckerboardTexture.hpp"

#include <filesystem>
#include <memory>
#include <utility>
#include <vector>

ScenePreset scenes::threeSpheres::makeScene() {
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
            Vec3{0.0f, -1.0f, 0.5f},
            Vec3{0.1f, 0.1f, 0.3f}
        )
    };

    const Material sphereMaterial{
        {0.3f, 0.6f, 0.9f},
        {1.0f, 1.0f, 1.0f},
        32.0f
    };
    Material reflectiveSphereMaterial = sphereMaterial;
    reflectiveSphereMaterial.reflectiveness = 1.0f;
    constexpr float sphereRadius = 0.5f;

    ObjectPtr toonSphere = std::make_shared<Sphere>(
        Vec3{-1.05f, 0.0f, 1.0f},
        sphereRadius,
        sphereMaterial,
        std::make_shared<ToonShader>()
    );
    ObjectPtr ambientSphere = std::make_shared<Sphere>(
        Vec3{0.0f, 0.0f, 1.0f},
        sphereRadius,
        reflectiveSphereMaterial,
        std::make_shared<BlinnPhongShader>()
    );
    ObjectPtr blinnPhongSphere = std::make_shared<Sphere>(
        Vec3{1.05f, 0.0f, 1.0f},
        sphereRadius,
        sphereMaterial,
        std::make_shared<BlinnPhongShader>()
    );

    const Material planeMaterial{
        {0.35f, 0.35f, 0.35f},
        {0.9f, 0.9f, 0.9f},
        16.0f,
        std::make_shared<CheckerboardTexture>(
            Vec3{0.0f, 0.0f, 0.0f},
            Vec3{0.85f, 0.85f, 0.85f},
            1.0f
        )
    };
    ObjectPtr plane = std::make_shared<Plane>(
        Vec3{0.0f, 0.0f, 0.0f},
        Vec3{0.0f, 0.0f, 1.0f},
        planeMaterial,
        std::make_shared<BlinnPhongShader>(),
        Vec3{1.0f, 0.0f, 0.0f},
        Vec3{0.0f, 1.0f, 0.0f}
    );

    std::vector<ObjectPtr> objects{
        std::move(toonSphere),
        std::move(ambientSphere),
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
        std::filesystem::path{GRAPHICS_RENDER_DIR} / "ThreeSpheres.ppm"
    };
}

namespace scenes::threeSpheres {
    const ScenePreset preset = makeScene();
}
