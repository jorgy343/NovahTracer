#include "NovahTracerEngine.h"

MaterialBase::MaterialBase(
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
    _ambientCoefficient(ambientCoefficient),
    _diffuseCoefficient(diffuseCoefficient),
    _specularCoefficient(specularCoefficient),
    _reflectionCoefficient(reflectionCoefficient),
    _refractionCoefficient(refractionCoefficient),
    _specularPower(specularPower),
    _refractionIndex(refractionIndex),
    _lightOccluder(lightOccluder),
    _shadowReceiver(shadowReceiver)
{

}

PropertyGetSetImplementation(float, MaterialBase, ambientCoefficient, AmbientCoefficient)
PropertyGetSetImplementation(float, MaterialBase, diffuseCoefficient, DiffuseCoefficient)
PropertyGetSetImplementation(float, MaterialBase, specularCoefficient, SpecularCoefficient)
PropertyGetSetImplementation(float, MaterialBase, reflectionCoefficient, ReflectionCoefficient)
PropertyGetSetImplementation(float, MaterialBase, refractionCoefficient, RefractionCoefficient)
PropertyGetSetImplementation(float, MaterialBase, specularPower, SpecularPower)
PropertyGetSetImplementation(float, MaterialBase, refractionIndex, RefractionIndex)

PropertyGetSetImplementation(bool, MaterialBase, lightOccluder, LightOccluder)
PropertyGetSetImplementation(bool, MaterialBase, shadowReceiver, ShadowReceiver)