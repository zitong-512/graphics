#include "FrameRenderer.hpp"

#include "Renderers/Renderer.hpp"
#include "Scenes/Scene.hpp"

#include <algorithm>
#include <atomic>
#include <stdexcept>
#include <thread>

namespace {
std::uint8_t toByte(float value) {
    return static_cast<std::uint8_t>(
        255.999f * std::clamp(value, 0.0f, 1.0f));
}

std::size_t pixelIndex(int x, int y, int width) {
    return static_cast<std::size_t>(y) * static_cast<std::size_t>(width) +
           static_cast<std::size_t>(x);
}

void writePixel(std::vector<std::uint8_t>& pixels, std::size_t pixel,
    const Vec3& color) {
    const std::size_t byteIndex = 3 * pixel;
    pixels[byteIndex] = toByte(color.x);
    pixels[byteIndex + 1] = toByte(color.y);
    pixels[byteIndex + 2] = toByte(color.z);
}

template <typename Function>
void parallelForRows(int height, const Function& function) {
    std::atomic<int> nextRow{0};
    const unsigned int availableThreads =
        std::max(1u, std::thread::hardware_concurrency());
    const unsigned int threadCount =
        std::min(availableThreads, static_cast<unsigned int>(height));

    const auto worker = [&]() {
        while (true) {
            const int y = nextRow.fetch_add(1, std::memory_order_relaxed);
            if (y >= height) { break; }
            function(y);
        }
    };

    std::vector<std::thread> workers;
    workers.reserve(threadCount);
    for (unsigned int i = 0; i < threadCount; ++i) {
        workers.emplace_back(worker);
    }
    for (std::thread& thread : workers) { thread.join(); }
}
} // namespace

FrameRenderer::FrameRenderer(int width, int height, int maxRayDepth)
    : width_(width), height_(height), maxRayDepth_(maxRayDepth) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Frame dimensions must be positive");
    }
}

std::vector<std::uint8_t> FrameRenderer::render(
    const Scene& scene, const Renderer& renderer) const {
    const std::size_t pixelCount =
        static_cast<std::size_t>(width_) * static_cast<std::size_t>(height_);
    std::vector<std::uint8_t> pixels(pixelCount * 3);

    parallelForRows(height_, [&](int y) {
        for (int x = 0; x < width_; ++x) {
            const Ray ray = scene.camera().rayForPixel(
                static_cast<float>(x), static_cast<float>(y), width_, height_);
            const std::size_t index = pixelIndex(x, y, width_);
            const Vec3 color = renderer.color(scene, ray, maxRayDepth_);
            writePixel(pixels, index, color);
        }
    });

    return pixels;
}
