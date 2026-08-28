#pragma once

#include "Scenes/ScenePreset.hpp"

namespace scenes::threeSpheres {
    ScenePreset makeScene();
    extern const ScenePreset preset;
}

namespace scenes {
    using threeSpheres::makeScene;
    using threeSpheres::preset;
}
