#include "FrameRenderer.hpp"
#include "Objects/Sphere.hpp"
#include "Renderers/Raytracing.hpp"
#include "Renderers/Raymarching.hpp"
#include "Scenes/Presets/ObjectPlaneScene.hpp"

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
constexpr int framesPerSecond = 3;
constexpr int frameCount = 2 * framesPerSecond;

Scene& sceneForFrame(Scene& scene, int frame) {
    auto sphere = std::dynamic_pointer_cast<Sphere>(scene.objects().at(0));
    if (sphere) {
        // Change sphere position
        sphere->setCenter(sphere->center() + Vec3{0.0f, 0.0f, 0.5f});
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
    Raymarching renderer;
    const FrameRenderer frameRenderer{width, height};

    const std::filesystem::path renderDirectory = preset.outputPath().parent_path();
    const std::filesystem::path framesDirectory = renderDirectory / "video_frames";
    const std::filesystem::path videoPath = renderDirectory / "ObjectPlane.mp4";
    std::filesystem::create_directories(framesDirectory);

    for (int frame = 0; frame < frameCount; ++frame) {
        const Scene& animatedScene = sceneForFrame(scene, frame);
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
