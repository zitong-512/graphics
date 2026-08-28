#pragma once

#include "Lights/PointLight.hpp"
#include "Scenes/Scene.hpp"
#include "Utilities/Hit.hpp"
#include "Utilities/Ray.hpp"

#include <optional>
#include <vector>

class Renderer {
public:
    Renderer(float maxDistance = 100.0f,
             float shadowBias = 0.002f)
        : maxDistance_(maxDistance),
          shadowBias_(shadowBias) {}
    virtual ~Renderer() = default;

    float shadow(const Scene& scene,
                 const Hit& hit,
                 const PointLight& light) const;
    Vec3 color(const Scene& scene, const Ray& ray) const;

protected:
    virtual std::optional<Hit> closestHit(const Scene& scene,
                                          const Ray& ray,
                                          float maxDistance) const = 0;
    virtual std::optional<float> exitDistance(const Object& object,
                                              const Ray& ray,
                                              float maxDistance) const = 0;

    float maxDistance() const { return maxDistance_; }
    float shadowBias() const { return shadowBias_; }

private:
    std::vector<LightPtr> visibleLights(const Scene& scene,
                                        const Hit& hit) const;
    Vec3 localColor(const Scene& scene, const Hit& hit) const;
    Vec3 reflectionColor(const Scene& scene,
                         const Ray& incomingRay,
                         const Hit& hit) const;
    Ray reflectedRay(const Ray& incomingRay, const Hit& hit) const;

    float maxDistance_;
    float shadowBias_;
};
