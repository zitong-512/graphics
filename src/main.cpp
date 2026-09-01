#include "Renders/Raymarching.hpp"
#include "Scenes/Presets/ThreeSpheresScene.hpp"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

namespace {
    std::uint8_t toByte(float value) {
        return static_cast<std::uint8_t>(255.999f * std::clamp(value, 0.0f, 1.0f));
    }

    Vec3 colorForPixel(int x, int y, int width, int height, Scene scene, Raymarching raymarching){
        Ray ray = scene.camera().rayForPixel(static_cast<float>(x), static_cast<float>(y), width, height);
        Vec3 color = raymarching.color(scene, ray);
        return color;
    }
}

int main() {
    constexpr int width = 800;
    constexpr int height = 600;

    const ScenePreset& preset = scenes::threeSpheres::preset;
    const Scene& scene = preset.scene();
    Raymarching raymarching;

    std::vector<std::uint8_t> pixels;
    pixels.reserve(static_cast<std::size_t>(width) * height * 3);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const Vec3 color = colorForPixel(x, y, width, height, scene, raymarching);

            pixels.push_back(toByte(color.x));
            pixels.push_back(toByte(color.y));
            pixels.push_back(toByte(color.z));
        }
    }

    std::filesystem::create_directories(preset.outputPath().parent_path());
    std::ofstream output(preset.outputPath(), std::ios::binary);
    if (!output) {
        std::cerr << "Unable to open output file: "
                  << preset.outputPath() << '\n';
        return 1;
    }
    output << "P6\n" << width << ' ' << height << "\n255\n";
    output.write(
        reinterpret_cast<const char*>(pixels.data()),
        static_cast<std::streamsize>(pixels.size())
    );
    
    return 0;
}
