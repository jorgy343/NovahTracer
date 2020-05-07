#pragma once

#include "NovahTracerEngine.h"

using namespace Novah::AdvancedMath;

class SpotLight : public PointLight, public DirectionalLight
{
private:
    float _umbraAngle;
    float _penumbraAngle;

protected:
    float _falloff;

public:
    SpotLight(const Color3& color, const Vector3& position, const Vector3& direction, float umbraAngle, float penumbraAngle, float falloff);

    virtual float GetShadowPower(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const * surfaces, int surfaceCount) const;
    virtual void GetLightPowers(const Ray& viewRay, const Vector3& point, const Vector3& normal, float* diffusePower, float* specularPower) const;

    float GetUmbraAngle() const;
    void SetUmbraAngle(float umbraAngle);

    float GetPenumbraAngle() const;
    void SetPenumbraAngle(float penumbraAngle);

    float GetFalloff() const;
    void SetFalloff(float falloff);
};