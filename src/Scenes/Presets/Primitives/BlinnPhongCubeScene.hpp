#pragma once

#include "Scenes/ScenePreset.hpp"

namespace scenes::blinnPhongCube {
    ScenePreset makeScene();
    extern const ScenePreset preset;
}

namespace scenes {
    using blinnPhongCube::makeScene;
    using blinnPhongCube::preset;
}