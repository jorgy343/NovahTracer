#pragma once

#include "NovahTracerEngine.h"

using namespace Novah::AdvancedMath;

class SphericalLight : public PointLight
{
protected:
    float _radius;

    Vector3 GetRandomPointOnSphere(Vector3 spherePosition, float sphereRadius) const;

public:
    SphericalLight(const Color3& color, const Vector3& position, float radius);
    SphericalLight(const Color3& color, const Sphere& sphere);

    virtual float GetShadowPower(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const * surfaces, int surfaceCount) const;
    virtual void GetLightPowers(const Ray& viewRay, const Vector3& point, const Vector3& normal, float* diffusePower, float* specularPower) const;

    Sphere GetSphere() const;
    void SetSphere(const Sphere& sphere);

    float GetRadius() const;
    void SetRadius(float radius);
};