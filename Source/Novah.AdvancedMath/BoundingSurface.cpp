#include "NovahAdvancedMath.h"

using namespace Novah::AdvancedMath;

BoundingSurface::BoundingSurface(const Surface* bounder, const Surface* surface)
    : _bounder(bounder), _surface(surface)
{

}

const Surface* BoundingSurface::IntersectRay(const Ray& ray, IntersectionData* intersectionData) const
{
    IntersectionData tempIntersectionData;
    if (_bounder->IntersectRay(ray, &tempIntersectionData) == nullptr)
        return nullptr;

    return _surface->IntersectRay(ray, intersectionData);
}

const Surface* BoundingSurface::IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const
{
    IntersectionData tempIntersectionData;
    if (_bounder->IntersectRay(ray, &tempIntersectionData) == nullptr)
        return nullptr;

    return _surface->IntersectRay(ray, intersectionData);
}

const Surface* BoundingSurface::GetBounder() const
{
    return _bounder;
}

const Surface* BoundingSurface::GetSurface() const
{
    return _surface;
}