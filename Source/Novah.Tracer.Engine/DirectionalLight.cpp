#include "NovahTracerEngine.h"

DirectionalLight::DirectionalLight(const Color3& color, const Vector3& direction)
    : Light(color), _direction(direction)
{

}

float DirectionalLight::GetShadowPower(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const * surfaces, int surfaceCount) const
{
    Ray ray(point + Epsilon * GetReversedDirection(), GetReversedDirection());

    IntersectionData intersectionData;
    for (int i = 0; i < surfaceCount; ++i)
    {
        if (surfaces[i]->IntersectRay(ray, &intersectionData))
            return 0.0f;
    }

    return 1.0f;
}

void DirectionalLight::GetLightPowers(const Ray& viewRay, const Vector3& point, const Vector3& normal, float* diffusePower, float* specularPower) const
{
    Vector3 lightReflectionOffNormal = Vector3::Reflect(GetReversedDirection(), normal).Normalize();

    *diffusePower = std::max(0.0f, Vector3::Dot(normal, GetReversedDirection()));
    *specularPower = Vector3::Dot(lightReflectionOffNormal, Vector3::Negate(viewRay.Direction));
}

Vector3 DirectionalLight::GetReversedDirection() const
{
    return Vector3::Negate(_direction);
}

Vector3 DirectionalLight::GetDirection() const
{
    return _direction;
}

void DirectionalLight::SetDirection(const Vector3& direction)
{
    _direction = direction;
}