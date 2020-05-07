#include "NovahTracerEngine.h"

AttenuatedLight::AttenuatedLight(const Color3& color, float constantAttenuationFactor, float linearAttenuationFactor, float quadraticAttenuationFactor)
    : Light(color),
    _constantAttenuationFactor(constantAttenuationFactor),
    _linearAttenuationFactor(linearAttenuationFactor),
    _quadraticAttenuationFactor(quadraticAttenuationFactor)
{

}

float AttenuatedLight::GetAttenuationPower(float distance) const
{
    float distanceSquared = distance * distance;
    return 1.0f / (_constantAttenuationFactor + _linearAttenuationFactor * distance + _quadraticAttenuationFactor * distanceSquared);
}

float AttenuatedLight::GetAttenuationPower(const Vector3& point1, const Vector3& point2) const
{
    return GetAttenuationPower((point2 - point1).GetLength());
}

float AttenuatedLight::GetConstantAttenuationFactor() const
{
    return _constantAttenuationFactor;
}

void AttenuatedLight::SetConstantAttenuationFactor(float constantAttenuationFactor)
{
    _constantAttenuationFactor = constantAttenuationFactor;
}

float AttenuatedLight::GetLinearAttenuationFactor() const
{
    return _linearAttenuationFactor;
}

void AttenuatedLight::SetLinearAttenuationFactor(float linearAttenuationFactor)
{
    _linearAttenuationFactor = linearAttenuationFactor;
}

float AttenuatedLight::GetQuadraticAttenuationFactor() const
{
    return _quadraticAttenuationFactor;
}

void AttenuatedLight::SetQuadraticAttenuationFactor(float quadraticAttenuationFactor)
{
    _quadraticAttenuationFactor = quadraticAttenuationFactor;
}