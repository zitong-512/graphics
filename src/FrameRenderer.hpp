#pragma once

#include <cstdint>
#include <vector>

class Renderer;
class Scene;

class FrameRenderer {
public:
    FrameRenderer(int width, int height, int maxRayDepth = 10);

    std::vector<std::uint8_t> render(
        const Scene& scene, const Renderer& renderer) const;

    int width() const { return width_; }
    int height() const { return height_; }

private:
    int width_;
    int height_;
    int maxRayDepth_;
};
