#pragma once

#include "NovahTracerEngine.h"
#include <functional>

using namespace Novah::AdvancedMath;

class FunctionMaterial : public MaterialBase
{
private:
    Color3 _specularColor;
    std::function<Color3(const Vector3* point, const Vector3* normal)> _shader;

public:
    FunctionMaterial(
        std::function<Color3(const Vector3* point, const Vector3* normal)> shader,
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

    PropertyGetSetDeclaration(const Color3&, specularColor, SpecularColor)
    PropertyGetSetDeclaration(std::function<Color3(const Vector3* point, const Vector3* normal)>, shader, Shader)
};