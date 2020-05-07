#include "NovahTracerEngine.h"

Vector3 SphericalLight::GetRandomPointOnSphere(Vector3 spherePosition, float sphereRadius) const
{
    float u = (float)(rand() % 10000) / 10000.0f;
    float v = (float)(rand() % 10000) / 10000.0f;

    float theta = 2.0f * M_PI * u;
    float phi = acos(2.0f * v - 1.0f);

    float x = spherePosition.X + sphereRadius * sin(phi) * cos(theta);
    float y = spherePosition.Y + sphereRadius * sin(phi) * sin(theta);
    float z = spherePosition.Z + sphereRadius * cos(phi);

    return Vector3(x, y, z);
}

SphericalLight::SphericalLight(const Color3& color, const Vector3& position, float radius)
    : Light(color), PointLight(color, position), _radius(radius)
{

}

SphericalLight::SphericalLight(const Color3& color, const Sphere& sphere)
    : Light(color), PointLight(color, sphere.Position), _radius(sphere.Radius)
{

}

float SphericalLight::GetShadowPower(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const * surfaces, int surfaceCount) const
{
    float shadowPower = 200.0f;
    for (int i = 0; i < 200; ++i)
    {
        Vector3 randomPoint = GetRandomPointOnSphere(_position, _radius);

        Vector3 directionToLight = (randomPoint - point).Normalize();
        Ray ray(point + Epsilon * directionToLight, directionToLight);
        float distanceToLight = (randomPoint - point).GetLength();

        IntersectionData intersectionData;
        for (int i = 0; i < surfaceCount; ++i)
        {
            if (surfaces[i]->IntersectRay(ray, &intersectionData) && intersectionData.GetDistance() <= distanceToLight)
            {
                shadowPower -= 1.0f;
                continue;
            }
        }
    }

    return shadowPower / 200.0f;
}

void SphericalLight::GetLightPowers(const Ray& viewRay, const Vector3& point, const Vector3& normal, float* diffusePower, float* specularPower) const
{
    Vector3 directionToLight = (_position - point).Normalize();
    Vector3 lightReflectionOffNormal = Vector3::Reflect(directionToLight, normal).Normalize();

    *diffusePower = std::max(0.0f, Vector3::Dot(normal, directionToLight));
    *specularPower = Vector3::Dot(lightReflectionOffNormal, Vector3::Negate(viewRay.Direction));
}

Sphere SphericalLight::GetSphere() const
{
    return Sphere(_position, _radius);
}

void SphericalLight::SetSphere(const Sphere& sphere)
{
    _position = sphere.Position;
    _radius = sphere.Radius;
}

float SphericalLight::GetRadius() const
{
    return _radius;
}

void SphericalLight::SetRadius(float radius)
{
    _radius = radius;
}