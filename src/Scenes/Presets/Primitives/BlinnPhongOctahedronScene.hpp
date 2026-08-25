#pragma once

#include "Scenes/ScenePreset.hpp"

namespace scenes::blinnPhongOctahedron {
    ScenePreset makeScene();
    extern const ScenePreset preset;
}

namespace scenes {
    using blinnPhongOctahedron::makeScene;
    using blinnPhongOctahedron::preset;
}