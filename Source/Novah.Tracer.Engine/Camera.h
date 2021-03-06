#pragma once

#include "NovahTracerEngine.h"

using namespace Novah::AdvancedMath;

class Camera
{
private:
    Vector3 _position, _lookAt, _up;
    int _screenWidth, _screenHeight;

protected:
    mutable Random _random;
    Camera(const Vector3& position, const Vector3& lookAt, const Vector3& up, int screenWidth, int screenHeight);

public:
    virtual void CalculateRays(int x, int y, int level, Ray* rays) const = 0;

    Vector3 GetPosition() const;
    void SetPosition(const Vector3& position);

    Vector3 GetLookAt() const;
    void SetLookAt(const Vector3& lookAt);

    Vector3 GetUp() const;
    void SetUp(const Vector3& up);

    int GetScreenWidth() const;
    void SetScreenWidth(int screenWidth);

    int GetScreenHeight() const;
    void SetScreenHeight(int screenHeight);
};