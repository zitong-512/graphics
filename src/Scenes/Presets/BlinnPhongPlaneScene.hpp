#pragma once

#include "Scenes/ScenePreset.hpp"

namespace scenes::blinnPhongPlane {
    ScenePreset makeScene();
    extern const ScenePreset preset;
}

namespace scenes {
    using blinnPhongPlane::makeScene;
    using blinnPhongPlane::preset;
}