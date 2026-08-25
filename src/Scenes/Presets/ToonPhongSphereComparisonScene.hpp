#pragma once

#include "Scenes/ScenePreset.hpp"

namespace scenes::toonPhongSphereComparison {
    ScenePreset makeScene();
    extern const ScenePreset preset;
}

namespace scenes {
    using toonPhongSphereComparison::makeScene;
    using toonPhongSphereComparison::preset;
}