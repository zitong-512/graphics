#pragma once

#include "Scenes/ScenePreset.hpp"

namespace scenes::blinnPhongCone {
    ScenePreset makeScene();
    extern const ScenePreset preset;
}

namespace scenes {
    using blinnPhongCone::makeScene;
    using blinnPhongCone::preset;
}