#pragma once

#include "Scenes/ScenePreset.hpp"

namespace scenes::blinnPhongDodecahedron {
    ScenePreset makeScene();
    extern const ScenePreset preset;
}

namespace scenes {
    using blinnPhongDodecahedron::makeScene;
    using blinnPhongDodecahedron::preset;
}
