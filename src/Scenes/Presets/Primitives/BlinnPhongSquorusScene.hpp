#pragma once

#include "Scenes/ScenePreset.hpp"

namespace scenes::blinnPhongSquorus {
    ScenePreset makeScene();
    extern const ScenePreset preset;
}

namespace scenes {
    using blinnPhongSquorus::makeScene;
    using blinnPhongSquorus::preset;
}
