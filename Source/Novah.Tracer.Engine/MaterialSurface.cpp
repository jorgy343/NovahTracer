#include "NovahTracerEngine.h"

MaterialSurface::MaterialSurface(const MaterialBase* material, const Surface* surface)
    : _material(material), _surface(surface)
{

}

const MaterialBase* MaterialSurface::GetMaterial() const
{
    return _material;
}

const Surface* MaterialSurface::GetSurface() const
{
    return _surface;
}