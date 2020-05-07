#include "NovahTracerEngine.h"
#include <functional>

FunctionMaterial::FunctionMaterial(
    std::function<Color3(const Vector3* point, const Vector3* normal)> shader,
    const Color3& specularColor,
    float ambientCoefficient,
    float diffuseCoefficient,
    float specularCoefficient,
    float reflectionCoefficient,
    float refractionCoefficient,
    float specularPower,
    float refractionIndex,
    bool lightOccluder,
    bool shadowReceiver)
    :
    MaterialBase(
        ambientCoefficient,
        diffuseCoefficient,
        specularCoefficient,
        reflectionCoefficient,
        refractionCoefficient,
        specularPower,
        refractionIndex,
        lightOccluder,
        shadowReceiver),
    _shader(shader),
    _specularColor(specularColor)
{

}

Color3 FunctionMaterial::CalculateColor(const Vector3* point, const Vector3* normal) const
{
    return _shader(point, normal);
}

Color3 FunctionMaterial::CalculateSpecularColor(const Vector3* point, const Vector3* normal) const
{
    return _specularColor;
}

PropertyGetSetImplementation(const Color3&, FunctionMaterial, specularColor, SpecularColor)
PropertyGetSetImplementation(std::function<Color3(const Vector3* point, const Vector3* normal)>, FunctionMaterial, shader, Shader)