#pragma once

#include "NovahTracerEngine.h"

using namespace Novah::AdvancedMath;

class ParallelogramLight : virtual public Light
{
protected:
    Vector3 _corner, _edge1, _edge2;
    int _sampleLevel;
    ParallelogramLightSampleMode _parallelogramLightSampleMode;

    float GetShadowPowerRandom(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const * surfaces, int surfaceCount) const;
    float GetShadowPowerRegular(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const * surfaces, int surfaceCount) const;
    float GetShadowPowerRegularRandom(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const * surfaces, int surfaceCount) const;

public:
    ParallelogramLight(const Color3& color, const Vector3& corner, const Vector3& edge1, const Vector3& edge2, int sampleLevel, ParallelogramLightSampleMode parallelogramLightSampleMode);

    virtual float GetShadowPower(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const * surfaces, int surfaceCount) const;
    virtual void GetLightPowers(const Ray& viewRay, const Vector3& point, const Vector3& normal, float* diffusePower, float* specularPower) const;

    Vector3 GetCorner() const;
    void SetCorner(const Vector3& corner);

    Vector3 GetEdge1() const;
    void SetEdge1(const Vector3& edge1);

    Vector3 GetEdge2() const;
    void SetEdge2(const Vector3& edge2);
};