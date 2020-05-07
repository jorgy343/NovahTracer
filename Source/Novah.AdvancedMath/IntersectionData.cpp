#include "NovahAdvancedMath.h"

using namespace Novah::AdvancedMath;

IntersectionData::IntersectionData(float distance, const Vector3& point, const Vector3& normal, const Surface* collisionSurface, const Surface* detailedSurface)
    : _distance(distance), _point(point), _normal(normal), _collisionSurface(collisionSurface), _detailedSurface(detailedSurface)
{

}

float IntersectionData::GetDistance() const
{
    return _distance;
}

void IntersectionData::SetDistance(float distance)
{
    _distance = distance;
}

Vector3 IntersectionData::GetPoint() const
{
    return _point;
}

void IntersectionData::SetPoint(const Vector3& point)
{
    _point = point;
}

Vector3 IntersectionData::GetNormal() const
{
    return _normal;
}

void IntersectionData::SetNormal(const Vector3& normal)
{
    _normal = normal;
}

const Surface* IntersectionData::GetCollisionSurface() const
{
    return _collisionSurface;
}

void IntersectionData::SetCollisionSurface(const Surface* collisionSurface)
{
    _collisionSurface = collisionSurface;
}

const Surface* IntersectionData::GetDetailedSurface() const
{
    return _detailedSurface;
}

void IntersectionData::SetDetailedSurface(const Surface* detailedSurface)
{
    _detailedSurface = detailedSurface;
}