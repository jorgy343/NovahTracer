#pragma once

#include "NovahTracerEngine.h"

using namespace Novah::AdvancedMath;

class OrthographicCamera : public Camera
{
private:
    float _orthoWidth, _orthoHeight;

public:
    OrthographicCamera(const Vector3& position, const Vector3& lookAt, const Vector3& up, int screenWidth, int screenHeight, float orthoWidth, float orthoHeight);

    virtual void CalculateRays(int x, int y, int level, Ray* rays) const override;

    float GetOrthoWidth() const;
    void SetOrthoWidth(float orthoWidth);

    float GetOrthoHeight() const;
    void SetOrthoHeight(float orthoHeight);
};