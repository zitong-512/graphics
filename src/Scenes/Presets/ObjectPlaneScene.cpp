#include "Scenes/Presets/ObjectPlaneScene.hpp"

#include "Lights/AmbientLight.hpp"
#include "Lights/PointLight.hpp"
#include "Materials/Material.hpp"
#include "Objects/Cube.hpp"
#include "Objects/MorphObject.hpp"
#include "Objects/Plane.hpp"
#include "Objects/Sphere.hpp"
#include "Shaders/BlinnPhongShader.hpp"
#include "Textures/BandsTexture.hpp"
#include "Textures/CheckerboardTexture.hpp"

#include <filesystem>
#include <memory>
#include <utility>
#include <vector>

ScenePreset scenes::objectPlane::makeScene() {
    Camera camera{
        {1.0f, -2.0f, 2.5f}, // Position
        {0.0f, 1.0f, 0.0f},  // Target
        {0.0f, 0.0f, 1.0f},  // Up
        32.0f / 9.0f,        // Viewport width
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

    const Material baseObjectMaterial{
        {0.3f, 0.6f, 0.9f},
        {1.0f, 1.0f, 1.0f},
        32.0f
    };
    Material objectMaterial = baseObjectMaterial;
    objectMaterial.colorTexture = std::make_shared<BandsTexture>(
        Vec3{0.04f, 0.12f, 0.22f},
        Vec3{0.45f, 0.85f, 1.0f},
        10
    );
    objectMaterial.reflectiveness = 0.0f;
    objectMaterial.transmissivity = 0.0f;
    objectMaterial.refractiveIndex = 1.5f;
    constexpr float objectRadius = 0.5f;
    const Vec3 objectCenter{0.0f, 0.0f, 1.0f};
    const auto objectShader = std::make_shared<BlinnPhongShader>();

    ObjectPtr sphere = std::make_shared<Sphere>(
        objectCenter,
        objectRadius,
        objectMaterial,
        objectShader
    );
    ObjectPtr sphere2 = std::make_shared<Sphere>(
        objectCenter + Vec3({0.0f, 5.0f, 0.0f}),
        objectRadius,
        objectMaterial,
        objectShader
    );

    /*
    ObjectPtr cube = std::make_shared<Cube>(
        objectCenter,
        objectRadius,
        objectMaterial,
        objectShader
    );
    ObjectPtr object = std::make_shared<MorphObject>(
        std::move(sphere),
        std::move(cube),
        objectMaterial,
        objectShader
    );
    */

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
        std::move(sphere),
        std::move(sphere2),
        std::move(plane)
    };

    return ScenePreset{
        Scene{
            std::move(camera),
            background,
            std::move(lights),
            std::move(objects)
        },
        std::filesystem::path{GRAPHICS_RENDER_DIR} / "ObjectPlane.ppm"
    };
}

namespace scenes::objectPlane {
    const ScenePreset preset = makeScene();
}
