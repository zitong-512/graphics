#pragma once

#include "Scenes/ScenePreset.hpp"

namespace scenes::toonSphere {
    ScenePreset makeScene();
    extern const ScenePreset preset;
}

namespace scenes {
    using toonSphere::makeScene;
    using toonSphere::preset;
}