#pragma once

#include "NovahTracerEngine.h"
#include <functional>

using namespace Novah::AdvancedMath;

class BasicMaterial : public MaterialBase
{
private:
    Color3 _color;
    Color3 _specularColor;

public:
    BasicMaterial(
        const Color3& color,
        const Color3& specularColor,
        float ambientCoefficient,
        float diffuseCoefficient,
        float specularCoefficient,
        float reflectionCoefficient,
        float refractionCoefficient,
        float specularPower,
        float refractionIndex,
        bool _lightOccluder = false,
        bool _shadowReceiver = false);

    virtual Color3 CalculateColor(const Vector3* point, const Vector3* normal) const override;
    virtual Color3 CalculateSpecularColor(const Vector3* point, const Vector3* normal) const override;

    PropertyGetSetDeclaration(const Color3&, color, Color)
    PropertyGetSetDeclaration(const Color3&, specularColor, SpecularColor)
};