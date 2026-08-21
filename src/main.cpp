#include "Renders/Raymarching.hpp"
#include "Shaders/BlinnPhong.hpp"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

namespace {
    std::uint8_t toByte(float value) {
        return static_cast<std::uint8_t>(255.999f * std::clamp(value, 0.0f, 1.0f));
    }
}

int main() {
    int width = 800;
    int height = 600;
    const char* outputPath = "imageeee.ppm";

    Scene scene;
    BlinnPhong shader;
    Raymarching raymarching;

    std::vector<std::uint8_t> pixels;
    pixels.reserve(static_cast<std::size_t>(width) * height * 3);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Ray ray = scene.camera().rayForPixel(x, y, width, height);
            Vec3 color = raymarching.color(scene, shader, ray);

            pixels.push_back(toByte(color.x));
            pixels.push_back(toByte(color.y));
            pixels.push_back(toByte(color.z));
        }
    }

    std::ofstream output(outputPath, std::ios::binary);
    output << "P6\n" << width << ' ' << height << "\n255\n";
    output.write(
        reinterpret_cast<const char*>(pixels.data()),
        static_cast<std::streamsize>(pixels.size())
    );
    
    return 0;
}
