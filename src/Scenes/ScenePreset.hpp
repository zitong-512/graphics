#pragma once

#include "Scenes/Scene.hpp"

#include <filesystem>
#include <utility>

#ifndef GRAPHICS_RENDER_DIR
#define GRAPHICS_RENDER_DIR "renders"
#endif

class ScenePreset {
public:
    ScenePreset(Scene scene, std::filesystem::path outputPath)
        : scene_(std::move(scene)), outputPath_(std::move(outputPath)) {}

    const Scene& scene() const { return scene_; }
    const std::filesystem::path& outputPath() const { return outputPath_; }

private:
    Scene scene_;
    std::filesystem::path outputPath_;
};
