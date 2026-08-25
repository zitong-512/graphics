#pragma once

#include "Scenes/ScenePreset.hpp"

namespace scenes::blinnPhongTetrahedron {
    ScenePreset makeScene();
    extern const ScenePreset preset;
}

namespace scenes {
    using blinnPhongTetrahedron::makeScene;
    using blinnPhongTetrahedron::preset;
}