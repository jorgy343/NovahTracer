#pragma once

#include "NovahTracerEngine.h"

using namespace Novah::AdvancedMath;

class PointLight : virtual public Light
{
protected:
    Vector3 _position;

public:
    PointLight(const Color3& color, const Vector3& position);

    virtual float GetShadowPower(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const * surfaces, int surfaceCount) const;
    virtual void GetLightPowers(const Ray& viewRay, const Vector3& point, const Vector3& normal, float* diffusePower, float* specularPower) const;

    Vector3 GetPosition() const;
    void SetPosition(const Vector3& position);
};