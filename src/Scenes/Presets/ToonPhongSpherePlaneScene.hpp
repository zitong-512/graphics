#pragma once

#include "Scenes/ScenePreset.hpp"

namespace scenes::toonPhongSpherePlane {
    ScenePreset makeScene();
    extern const ScenePreset preset;
}

namespace scenes {
    using toonPhongSpherePlane::makeScene;
    using toonPhongSpherePlane::preset;
}