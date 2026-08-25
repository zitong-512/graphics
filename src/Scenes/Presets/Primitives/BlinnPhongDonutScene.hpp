#pragma once

#include "Scenes/ScenePreset.hpp"

namespace scenes::blinnPhongDonut {
    ScenePreset makeScene();
    extern const ScenePreset preset;
}

namespace scenes {
    using blinnPhongDonut::makeScene;
    using blinnPhongDonut::preset;
}
