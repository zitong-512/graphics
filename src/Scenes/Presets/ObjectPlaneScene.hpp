#pragma once

#include "Scenes/ScenePreset.hpp"

namespace scenes::objectPlane {
    ScenePreset makeScene();
    extern const ScenePreset preset;
}

namespace scenes {
    using objectPlane::makeScene;
    using objectPlane::preset;
}
