#include "NovahTracerEngine.h"

PointLight::PointLight(const Color3& color, const Vector3& position)
    : Light(color), _position(position)
{

}

float PointLight::GetShadowPower(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const * surfaces, int surfaceCount) const
{
    Vector3 directionToLight = (_position - point).Normalize();
    Ray ray(point + Epsilon * normal, directionToLight);
    float distanceToLight = (_position - point).GetLength();

    IntersectionData intersectionData;
    for (int i = 0; i < surfaceCount; ++i)
    {
        if (surfaces[i]->IntersectRay(ray, &intersectionData) && intersectionData.GetDistance() <= distanceToLight)
            return 0.0f;
    }

    return 1.0f;
}

void PointLight::GetLightPowers(const Ray& viewRay, const Vector3& point, const Vector3& normal, float* diffusePower, float* specularPower) const
{
    Vector3 directionToLight = (_position - point).Normalize();
    Vector3 lightReflectionOffNormal = Vector3::Reflect(directionToLight, normal).Normalize();

    *diffusePower = std::max(0.0f, Vector3::Dot(normal, directionToLight));
    *specularPower = Vector3::Dot(lightReflectionOffNormal, Vector3::Negate(viewRay.Direction));
}

Vector3 PointLight::GetPosition() const
{
    return _position;
}

void PointLight::SetPosition(const Vector3& position)
{
    _position = position;
}