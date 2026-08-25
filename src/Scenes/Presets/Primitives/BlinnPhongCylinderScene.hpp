#pragma once

#include "Scenes/ScenePreset.hpp"

namespace scenes::blinnPhongCylinder {
    ScenePreset makeScene();
    extern const ScenePreset preset;
}

namespace scenes {
    using blinnPhongCylinder::makeScene;
    using blinnPhongCylinder::preset;
}