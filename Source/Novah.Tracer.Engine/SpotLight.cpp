#include "NovahTracerEngine.h"

SpotLight::SpotLight(const Color3& color, const Vector3& position, const Vector3& direction, float umbraAngle, float penumbraAngle, float falloff)
    : Light(color), PointLight(color, position), DirectionalLight(color, direction), _falloff(falloff)
{
    _umbraAngle = umbraAngle;
    _penumbraAngle = penumbraAngle;

    _umbraAngle = std::min((float)M_PI, std::max(0.0f, umbraAngle));
    _penumbraAngle = std::min((float)M_PI, std::max(_umbraAngle, _penumbraAngle));
}

float SpotLight::GetShadowPower(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const * surfaces, int surfaceCount) const
{
    return PointLight::GetShadowPower(viewRay, point, normal, surfaces, surfaceCount);
}

void SpotLight::GetLightPowers(const Ray& viewRay, const Vector3& point, const Vector3& normal, float* diffusePower, float* specularPower) const
{
    Vector3 directionFromLightToPoint = (_position - point).Normalize();
    float angleBetweenLightAndPoint = Vector3::Dot(directionFromLightToPoint, GetReversedDirection());

    float cosUmbraOver2 = std::cos(_umbraAngle / 2.0f);
    float cosPenumbraOver2 = std::cos(_penumbraAngle / 2.0f);

    float spotPower;
    if (angleBetweenLightAndPoint > cosUmbraOver2)
        spotPower = 1.0f;
    else if (angleBetweenLightAndPoint <= cosPenumbraOver2)
        spotPower = 0.0f;
    else
        spotPower = std::pow((angleBetweenLightAndPoint - cosPenumbraOver2) / (cosUmbraOver2 - cosPenumbraOver2), _falloff);

    PointLight::GetLightPowers(viewRay, point, normal, diffusePower, specularPower);

    *diffusePower *= spotPower;
    *specularPower *= spotPower;
}

float SpotLight::GetUmbraAngle() const
{
    return _umbraAngle;
}

void SpotLight::SetUmbraAngle(float umbraAngle)
{
    _umbraAngle = umbraAngle;

    _umbraAngle = std::min((float)M_PI, std::max(0.0f, umbraAngle));
    _penumbraAngle = std::min((float)M_PI, std::max(_umbraAngle, _penumbraAngle));
}

float SpotLight::GetPenumbraAngle() const
{
    return _penumbraAngle;
}

void SpotLight::SetPenumbraAngle(float penumbraAngle)
{
    _penumbraAngle = penumbraAngle;
    _penumbraAngle = std::min((float)M_PI, std::max(_umbraAngle, _penumbraAngle));
}

float SpotLight::GetFalloff() const
{
    return _falloff;
}

void SpotLight::SetFalloff(float falloff)
{
    _falloff = falloff;
}