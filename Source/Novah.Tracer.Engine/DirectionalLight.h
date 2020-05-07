#pragma once

#include "NovahTracerEngine.h"

using namespace Novah::AdvancedMath;

class DirectionalLight : virtual public Light
{
protected:
    Vector3 _direction;

public:
    DirectionalLight(const Color3& color, const Vector3& direction);

    virtual float GetShadowPower(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const * surfaces, int surfaceCount) const;
    virtual void GetLightPowers(const Ray& viewRay, const Vector3& point, const Vector3& normal, float* diffusePower, float* specularPower) const;

    Vector3 GetReversedDirection() const;

    Vector3 GetDirection() const;
    void SetDirection(const Vector3& direction);
};