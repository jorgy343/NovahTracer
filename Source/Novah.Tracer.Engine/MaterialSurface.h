#pragma once

#include "NovahTracerEngine.h"

using namespace Novah::AdvancedMath;

class MaterialSurface
{
private:
    const MaterialBase* _material;
    const Surface* _surface;

public:
    MaterialSurface(const MaterialBase* material, const Surface* _surface);

    const MaterialBase* GetMaterial() const;
    const Surface* GetSurface() const;
};