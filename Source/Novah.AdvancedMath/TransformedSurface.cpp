#include "NovahAdvancedMath.h"

using namespace Novah::AdvancedMath;

TransformedSurface::TransformedSurface(const Surface* surface, const Matrix& transform)
    : _surface(surface), _inversedTransform(Matrix::Invert(transform)), _inverseTransposedTransform(Matrix::Transpose(Matrix::Invert(transform)))
{

}

const Surface* TransformedSurface::IntersectRay(const Ray& ray, IntersectionData* intersectionData) const
{
    Ray transformedRay(
        Vector3(Matrix::Multiply(_inversedTransform, ray.Position, 1.0f)),
        Vector3(Matrix::Multiply(_inversedTransform, ray.Direction, 0.0f)));

    const Surface* result = _surface->IntersectRay(transformedRay, intersectionData);
    if (result == nullptr)
        return nullptr;

    intersectionData->SetNormal(Vector3(Matrix::Multiply(_inverseTransposedTransform, intersectionData->GetNormal(), 0.0f)).Normalize());
    intersectionData->SetPoint(ray.Position + intersectionData->GetDistance() * ray.Direction);
    intersectionData->SetCollisionSurface(this);
    intersectionData->SetDetailedSurface(_surface);

    return this;
}

const Surface* TransformedSurface::IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const
{
    Ray transformedRay(
        Vector3(Matrix::Multiply(_inversedTransform, ray.Position, 1.0f)),
        Vector3(Matrix::Multiply(_inversedTransform, ray.Direction, 0.0f)));

    const Surface* result = _surface->IntersectRay(transformedRay, intersectionData);
    if (result == nullptr)
        return nullptr;

    for (IntersectionData& singleIntersectionData : *intersectionData)
    {
        singleIntersectionData.SetNormal(Vector3(Matrix::Multiply(_inverseTransposedTransform, singleIntersectionData.GetNormal(), 0.0f)).Normalize());
        singleIntersectionData.SetPoint(ray.Position + singleIntersectionData.GetDistance() * ray.Direction);
        singleIntersectionData.SetCollisionSurface(this);
        singleIntersectionData.SetDetailedSurface(_surface);
    }

    return this;
}

const Surface* TransformedSurface::GetSurface() const
{
    return _surface;
}