#pragma once

#include "NovahTracerEngine.h"

using namespace Novah::AdvancedMath;

class Light
{
protected:
    Color3 _color;
    mutable Random _random;

    Light(const Color3& color);

public:
    virtual float GetShadowPower(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const * surfaces, int surfaceCount) const = 0;
    virtual void GetLightPowers(const Ray& viewRay, const Vector3& point, const Vector3& normal, float* diffusePower, float* specularPower) const = 0;

    Color3 GetColor() const;
    void SetColor(const Color3& color);
};