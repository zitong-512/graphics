#pragma once

#include "Scenes/ScenePreset.hpp"

namespace scenes::blinnPhongIcosahedron {
    ScenePreset makeScene();
    extern const ScenePreset preset;
}

namespace scenes {
    using blinnPhongIcosahedron::makeScene;
    using blinnPhongIcosahedron::preset;
}
