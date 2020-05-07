#pragma once

#include "NovahTracerEngine.h"

using namespace Novah::AdvancedMath;

class AttenuatedPointLight : public AttenuatedLight, public PointLight
{
protected:
    float _constantAttenuationFactor;
    float _linearAttenuationFactor;
    float _quadraticAttenuationFactor;

public:
    AttenuatedPointLight(const Color3& color, const Vector3& position, float constantAttenuationFactor, float linearAttenuationFactor, float quadraticAttenuationFactor);

    virtual void GetLightPowers(const Ray& viewRay, const Vector3& point, const Vector3& normal, float* diffusePower, float* specularPower) const;
};