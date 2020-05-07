#include "NovahAdvancedMath.h"

using namespace Novah::AdvancedMath;

BoundingVolume::BoundingVolume(const BoundingVolume& boundingVolume)
    : _surface(boundingVolume._surface)
{

}

BoundingVolume::BoundingVolume(const Surface* surface)
    : _surface(surface)
{

}

const Surface* BoundingVolume::GetSurface() const
{
    return _surface;
}