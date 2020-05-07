#include "NovahAdvancedMath.h"

using namespace Novah::AdvancedMath;

RectangularFrustum::RectangularFrustum(Plane near, Plane far, Plane left, Plane right, Plane top, Plane bottom)
    : Near(near), Far(far), Left(left), Right(right), Top(top), Bottom(bottom)
{

}

const Surface* RectangularFrustum::IntersectRay(const Ray& ray, IntersectionData* intersectionData) const
{
    return nullptr;
}

const Surface* RectangularFrustum::IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const
{
    return nullptr;
}