#pragma once

#include "NovahTracerEngine.h"
#include "LuaState.h"
#include "AdvancedMathLuaExtensions.h"

using namespace Novah::AdvancedMath;
using namespace Novah::Lua;

class LuaMaterial : public MaterialBase
{
private:
    LuaState* _luaState;

public:
    LuaMaterial(
        const char* luaCode,
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
};