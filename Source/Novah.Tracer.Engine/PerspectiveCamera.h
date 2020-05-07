#pragma once

#include "NovahTracerEngine.h"

using namespace Novah::AdvancedMath;

class PerspectiveCamera : public Camera
{
private:
    float _fieldOfView;

public:
    PerspectiveCamera(const Vector3& position, const Vector3& lookAt, const Vector3& up, int screenWidth, int screenHeight, float fieldOfView);

    virtual void CalculateRays(int x, int y, int level, Ray* rays) const override;

    float GetFieldOfView() const;
    void SetFieldOfView(float fieldOfView);
};