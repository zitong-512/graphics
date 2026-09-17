#include "FrameRenderer.hpp"
#include "Renders/RayTracing.hpp"
// #include "Scenes/Presets/Primitives/BlinnPhongPrimitiveScene.hpp"
#include "Scenes/Presets/ThreeSpheresScene.hpp"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
    const int width = 1920;
    const int height = 1080;

    const ScenePreset preset = scenes::makeScene();
    const Scene& scene = preset.scene();
    RayTracing renderer;
    const FrameRenderer frameRenderer{width, height};
    const std::vector<std::uint8_t> pixels = frameRenderer.render(scene, renderer);

    const std::filesystem::path& outputPath = preset.outputPath();
    std::filesystem::create_directories(outputPath.parent_path());

    std::ofstream output(outputPath, std::ios::binary);
    if (!output) {
        std::cerr << "Could not open output file: " << outputPath << '\n';
        return 1;
    }

    output << "P6\n" << width << ' ' << height << "\n255\n";
    output.write(reinterpret_cast<const char*>(pixels.data()),
        static_cast<std::streamsize>(pixels.size()));

    return output ? 0 : 1;
}
