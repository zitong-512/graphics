#pragma once

#include "Shaders/Shader.hpp"

class SpecularToonShader : public Shader {
public:
    SpecularToonShader(Vec3 objectColor = {0.85f, 0.4f, 0.15f},
                  Vec3 ambientLight = {0.55f, 0.55f, 0.85f},
                  Vec3 positionLight = {1.0f, 1.0f, 1.0f}, 
                  Vec3 cameraPosition = {0.0f, 0.0f, 0.0f})
        : objectColor_(objectColor),
          ambientLight_(ambientLight),
          positionLight_(positionLight),
          cameraPosition_(cameraPosition) {}

    Vec3 shade(const Hit& hit) const override;
        
 
private:
    Vec3 objectColor_; 
    Vec3 ambientLight_;
    Vec3 positionLight_;
    Vec3 cameraPosition_;
};
