#pragma once

#include "NovahTracerEngine.h"
#include <set>

using namespace Novah::AdvancedMath;

class Scene
{
private:
    Color3 _backgroundColor;
    float _defaultRefractionIndex;
    int _antiAliasingLevel;

    const Surface* _rootSurface;

    const std::unordered_map<const Surface*, const MaterialBase*>* _surfaceMaterialMap;
    const std::vector<const Light*>* _lights;

    std::vector<const Surface*> _lightOccluders;

    Color3 CastRay(const Ray& ray, int depth) const;

public:
    Scene(
        const Color3& backgroundColor,
        float defaultRefractionIndex,
        int antiAliasingLevel,
        const Surface* rootSurface,
        const std::unordered_map<const Surface*, const MaterialBase*>* surfaceMaterialMap,
        const std::vector<const Light*>* lights);

    Color3 CastRay(const Ray& ray) const;

    void SetRootSurface(const Surface* rootSurface);

    PropertyGetSetDeclaration(int, antiAliasingLevel, AntiAliasingLevel)
};