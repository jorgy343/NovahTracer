#pragma once

#include "NovahTracerEngine.h"

using namespace Novah::AdvancedMath;

class AttenuatedLight : virtual public Light
{
protected:
    float _constantAttenuationFactor;
    float _linearAttenuationFactor;
    float _quadraticAttenuationFactor;

    AttenuatedLight(const Color3& color, float constantAttenuationFactor, float linearAttenuationFactor, float quadraticAttenuationFactor);

public:
    float GetAttenuationPower(float distance) const;
    float GetAttenuationPower(const Vector3& point1, const Vector3& point2) const;

    float GetConstantAttenuationFactor() const;
    void SetConstantAttenuationFactor(float constantAttenuationFactor);

    float GetLinearAttenuationFactor() const;
    void SetLinearAttenuationFactor(float linearAttenuationFactor);

    float GetQuadraticAttenuationFactor() const;
    void SetQuadraticAttenuationFactor(float quadraticAttenuationFactor);
};