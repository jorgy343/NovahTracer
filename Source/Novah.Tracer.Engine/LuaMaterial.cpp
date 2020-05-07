#include "NovahTracerEngine.h"
#include "LuaState.h"

LuaMaterial::LuaMaterial(
    const char* luaCode,
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
        shadowReceiver)
{
    _luaState = new LuaState();
    luaL_openlibs(_luaState->GetInternalState());

    //auto perlinFunction = new LuaCFunction<double, double, double, double>(_luaState, "PerlinNoise3d", noise);
    _luaState->LoadStringAndExecute(luaCode);
}

Color3 LuaMaterial::CalculateColor(const Vector3* point, const Vector3* normal) const
{
    return _luaState->Call<Color3>("shade", *point, *normal);
}

Color3 LuaMaterial::CalculateSpecularColor(const Vector3* point, const Vector3* normal) const
{
    return Color3(1.0f);
}