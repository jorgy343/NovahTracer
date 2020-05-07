#pragma once

#include "NovahTracerEngine.h"

using namespace Novah::AdvancedMath;

class MaterialBase
{
private:
    float _ambientCoefficient;
    float _diffuseCoefficient;
    float _specularCoefficient;
    float _reflectionCoefficient;
    float _refractionCoefficient;

    float _specularPower;
    float _refractionIndex;

    bool _lightOccluder;
    bool _shadowReceiver;

public:
    MaterialBase(
        float ambientCoefficient,
        float diffuseCoefficient,
        float specularCoefficient,
        float reflectionCoefficient,
        float refractionCoefficient,
        float specularPower,
        float refractionIndex,
        bool _lightOccluder = false,
        bool _shadowReceiver = false);

    virtual Color3 CalculateColor(const Vector3* point, const Vector3* normal) const = 0;
    virtual Color3 CalculateSpecularColor(const Vector3* point, const Vector3* normal) const = 0;

    PropertyGetSetDeclaration(float, ambientCoefficient, AmbientCoefficient)
    PropertyGetSetDeclaration(float, diffuseCoefficient, DiffuseCoefficient)
    PropertyGetSetDeclaration(float, specularCoefficient, SpecularCoefficient)
    PropertyGetSetDeclaration(float, reflectionCoefficient, ReflectionCoefficient)
    PropertyGetSetDeclaration(float, refractionCoefficient, RefractionCoefficient)
    PropertyGetSetDeclaration(float, specularPower, SpecularPower)
    PropertyGetSetDeclaration(float, refractionIndex, RefractionIndex)

    PropertyGetSetDeclaration(bool, lightOccluder, LightOccluder)
    PropertyGetSetDeclaration(bool, shadowReceiver, ShadowReceiver)
};