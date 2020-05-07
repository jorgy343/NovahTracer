#include "NovahTracerEngine.h"

AttenuatedPointLight::AttenuatedPointLight(const Color3& color, const Vector3& position, float constantAttenuationFactor, float linearAttenuationFactor, float quadraticAttenuationFactor)
    : Light(color),
    AttenuatedLight(color, constantAttenuationFactor, linearAttenuationFactor, quadraticAttenuationFactor),
    PointLight(color, position),
    _constantAttenuationFactor(constantAttenuationFactor),
    _linearAttenuationFactor(linearAttenuationFactor),
    _quadraticAttenuationFactor(quadraticAttenuationFactor)
{

}

void AttenuatedPointLight::GetLightPowers(const Ray& viewRay, const Vector3& point, const Vector3& normal, float* diffusePower, float* specularPower) const
{
    float attenuation = GetAttenuationPower(GetPosition(), point);
    PointLight::GetLightPowers(viewRay, point, normal, diffusePower, specularPower);

    *diffusePower = *diffusePower * attenuation;
    *specularPower = *specularPower * attenuation;
}