#pragma once

#include "Materials/Material.hpp"
#include "Objects/Object.hpp"
#include "Scenes/ScenePreset.hpp"

#include <filesystem>

namespace scenes::blinnPhongPrimitive {
    Material objectMaterial();
    ScenePreset makeScene(ObjectPtr object,
                          const std::filesystem::path& outputFilename);
}
