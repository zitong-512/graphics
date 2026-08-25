#pragma once

#include "Scenes/ScenePreset.hpp"

namespace scenes::blinnPhongSphere {
    ScenePreset makeScene();
    extern const ScenePreset preset;
}

namespace scenes {
    using blinnPhongSphere::makeScene;
    using blinnPhongSphere::preset;
}