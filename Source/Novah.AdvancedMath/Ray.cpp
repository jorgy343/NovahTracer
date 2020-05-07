#include "NovahAdvancedMath.h"

using namespace Novah::AdvancedMath;

Ray::Ray(Vector3 position, Vector3 direction)
    : Position(position), Direction(direction)
{

}

const Surface* Ray::IntersectRay(const Ray& ray, IntersectionData* intersectionData) const
{
    return nullptr;
}

const Surface* Ray::IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const
{
    return nullptr;
}