#include "FrameRenderer.hpp"
#include "Objects/Sphere.hpp"
#include "Renderers/Raytracing.hpp"
#include "Renderers/Raymarching.hpp"
#include "Scenes/Presets/ObjectPlaneScene.hpp"
#include "Utilities/Transform.hpp"

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {
constexpr int width = 1920;
constexpr int height = 1080;
constexpr int framesPerSecond = 30;
constexpr int frameCount = 2 * framesPerSecond;
constexpr int halfFrameCount = frameCount / 2;
constexpr float pi = 3.14159;

Scene& sceneForFrame(Scene& scene, int frame) {
    auto sphere1 = std::dynamic_pointer_cast<Sphere>(scene.objects().at(0));
    auto sphere2 = std::dynamic_pointer_cast<Sphere>(scene.objects().at(1));
    if (!sphere1 || !sphere2) {
        return scene;
    }

    static const Vec3 initialSphere1Center = sphere1->getCenter();
    static const Vec3 initialSphere2Center = sphere2->getCenter();
    static const Vec3 initialSphere2Orientation = sphere2->getOrientation();
    static const float radius = sphere1->getRadius();
    static const float totalDisplacementY = -(
        std::abs(initialSphere1Center.y - initialSphere2Center.y)
        - 2.0f * radius
    );

    const float t = static_cast<float>(frame) / (frameCount - 1);
    const float displacementY = totalDisplacementY * t;

    if ( frame < halfFrameCount){
        sphere2->setCenter(
            initialSphere2Center + Vec3{0.0f, 2 * displacementY, 0.0f}
        );
        sphere2->setOrientation(initialSphere2Orientation
            - Vec3({frame * totalDisplacementY / halfFrameCount, 0.0f, 0.0f}));
    } else {
        sphere1->setCenter(
            initialSphere1Center + Vec3{0.0f, displacementY - totalDisplacementY / 2.0f, 0.0f}
        );
        sphere1->setOrientation(initialSphere2Orientation
            - Vec3({frame * totalDisplacementY / halfFrameCount, 0.0f, 0.0f}));
    }
    

    return scene;
}

[[maybe_unused]] Scene& sceneForFrameTransform(Scene& scene, int frame) {
    auto sphere1 = std::dynamic_pointer_cast<Sphere>(scene.objects().at(0));
    auto sphere2 = std::dynamic_pointer_cast<Sphere>(scene.objects().at(1));
    if (!sphere1 || !sphere2) {
        return scene;
    }

    static const Vec3 initialSphere1Center = sphere1->getCenter();
    static const Vec3 initialSphere2Center = sphere2->getCenter();
    static const Vec3 initialSphere1Orientation = sphere1->getOrientation();
    static const Vec3 initialSphere2Orientation = sphere2->getOrientation();
    static const float radius = sphere1->getRadius();
    static const float totalDisplacementY = -(
        std::abs(initialSphere1Center.y - initialSphere2Center.y)
        - 2.0f * radius
    );

    const auto orientationTransform = [](const Vec3& orientation) {
        return Transform::rotationZ(orientation.z)
            * Transform::rotationY(orientation.y)
            * Transform::rotationX(orientation.x);
    };

    const auto relativeOrientationTransform = [&](const Vec3& initial,
                                                   const Vec3& current) {
        return orientationTransform(current)
            * Transform::rotationX(-initial.x)
            * Transform::rotationY(-initial.y)
            * Transform::rotationZ(-initial.z);
    };

    const float t = static_cast<float>(frame) / (frameCount - 1);
    const float displacementY = totalDisplacementY * t;

    if (frame < halfFrameCount) {
        const Vec3 displacement{0.0f, 2.0f * displacementY, 0.0f};
        const Vec3 orientation = initialSphere2Orientation
            - Vec3{
                frame * totalDisplacementY / halfFrameCount,
                0.0f,
                0.0f
            };
        sphere2->setTransform(
            Transform::translation(displacement)
            * Transform::translation(initialSphere2Center)
            * relativeOrientationTransform(
                initialSphere2Orientation,
                orientation
            )
            * Transform::translation(-initialSphere2Center)
        );
    } else {
        const Vec3 displacement{
            0.0f,
            displacementY - totalDisplacementY / 2.0f,
            0.0f
        };
        const Vec3 orientation = initialSphere2Orientation
            - Vec3{
                frame * totalDisplacementY / halfFrameCount,
                0.0f,
                0.0f
            };
        sphere1->setTransform(
            Transform::translation(displacement)
            * Transform::translation(initialSphere1Center)
            * relativeOrientationTransform(
                initialSphere1Orientation,
                orientation
            )
            * Transform::translation(-initialSphere1Center)
        );
    }

    return scene;
}

std::filesystem::path framePath(
    const std::filesystem::path& directory, int frame) {
    std::ostringstream filename;
    filename << "frame_" << std::setfill('0') << std::setw(4) << frame << ".ppm";
    return directory / filename.str();
}

bool writePpm(const std::filesystem::path& path,
    const std::vector<std::uint8_t>& pixels) {
    std::ofstream output(path, std::ios::binary);
    if (!output) { return false; }

    output << "P6\n" << width << ' ' << height << "\n255\n";
    output.write(reinterpret_cast<const char*>(pixels.data()),
        static_cast<std::streamsize>(pixels.size()));
    return static_cast<bool>(output);
}

std::string quoted(const std::filesystem::path& path) {
    return '"' + path.string() + '"';
}
} // namespace

int main() {
    const ScenePreset preset = scenes::makeScene();
    Scene scene = preset.scene();
    Raytracing renderer;
    const FrameRenderer frameRenderer{width, height};

    const std::filesystem::path renderDirectory = preset.outputPath().parent_path();
    const std::filesystem::path framesDirectory = renderDirectory / "video_frames";
    const std::filesystem::path videoPath = renderDirectory / "ObjectPlane.mp4";
    std::filesystem::create_directories(framesDirectory);

    for (int frame = 0; frame < frameCount; ++frame) {
        const Scene& animatedScene = sceneForFrameTransform(scene, frame);
        const std::vector<std::uint8_t> pixels =
            frameRenderer.render(animatedScene, renderer);
        const std::filesystem::path outputPath = framePath(framesDirectory, frame);

        if (!writePpm(outputPath, pixels)) {
            std::cerr << "Could not write frame: " << outputPath << '\n';
            return 1;
        }

        std::cout << "Rendered frame " << frame + 1 << '/' << frameCount << '\r'
                  << std::flush;
    }
    std::cout << '\n';

    const std::filesystem::path inputPattern = framesDirectory / "frame_%04d.ppm";
    const std::string command =
        "ffmpeg -y -loglevel warning -framerate " +
        std::to_string(framesPerSecond) + " -i " + quoted(inputPattern) +
        " -frames:v " + std::to_string(frameCount) +
        " -c:v libx264 -pix_fmt yuv420p " + quoted(videoPath);

    if (std::system(command.c_str()) != 0) {
        std::cerr << "FFmpeg could not create the video. The rendered frames are in: "
                  << framesDirectory << '\n';
        return 1;
    }

    std::cout << "Created video: " << videoPath << '\n';
    return 0;
}
