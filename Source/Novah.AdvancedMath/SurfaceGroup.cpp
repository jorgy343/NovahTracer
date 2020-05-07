#include "NovahAdvancedMath.h"

using namespace Novah::AdvancedMath;

SurfaceGroup::SurfaceGroup(const std::vector<const Surface*>* surfaces)
    : _surfaces(surfaces)
{

}

const Surface* SurfaceGroup::IntersectRay(const Ray& ray, IntersectionData* intersectionData) const
{
    const Surface* closestSurface = nullptr;
    intersectionData->SetDistance(std::numeric_limits<float>::max());

    for (const auto& surface : *_surfaces)
    {
        IntersectionData foundIntersectionData;
        const Surface* foundSurface = surface->IntersectRay(ray, &foundIntersectionData);

        if (foundSurface != nullptr && foundIntersectionData.GetDistance() < intersectionData->GetDistance())
        {
            closestSurface = foundSurface;
            *intersectionData = foundIntersectionData;
        }
    }

    return closestSurface;
}

const Surface* SurfaceGroup::IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const
{
    return nullptr;
}