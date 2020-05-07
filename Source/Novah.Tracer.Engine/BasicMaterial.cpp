#include "NovahTracerEngine.h"
#include <functional>

BasicMaterial::BasicMaterial(
    const Color3& color,
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
    _color(color),
    _specularColor(specularColor)
{

}

Color3 BasicMaterial::CalculateColor(const Vector3* point, const Vector3* normal) const
{
    return _color;
}

Color3 BasicMaterial::CalculateSpecularColor(const Vector3* point, const Vector3* normal) const
{
    return _specularColor;
}

PropertyGetSetImplementation(const Color3&, BasicMaterial, color, Color)
PropertyGetSetImplementation(const Color3&, BasicMaterial, specularColor, SpecularColor)