#include "NovahAdvancedMath.h"

using namespace Novah::AdvancedMath;

Parallelogram::Parallelogram(const Vector3& corner, const Vector3& edge1, const Vector3& edge2)
    : Corner(corner), Edge1(edge1), Edge2(edge2)
{

}

const Surface* Parallelogram::IntersectRay(const Ray& ray, IntersectionData* intersectionData) const
{
    Vector3 P = Vector3::CrossProduct(ray.Direction, Edge2);
    float determinant = Vector3::Dot(Edge1, P);

    if (abs(determinant) < Epsilon)
        return nullptr;

    Vector3 T = ray.Position - Corner;
    float a = Vector3::Dot(T, P) / determinant;

    if (a < 0.0f || a > 1.0f)
        return nullptr;

    Vector3 Q = Vector3::CrossProduct(T, Edge1);
    float b = Vector3::Dot(ray.Direction, Q) / determinant;

    if (b < 0.0f || b > 1.0f)
        return nullptr;

    float distance = Vector3::Dot(Edge2, Q) / determinant;
    if (distance < 0.0f)
        return nullptr;

    Vector3 point = ray.Position + distance * ray.Direction;
    *intersectionData = IntersectionData(distance, ray.Position + distance * ray.Direction, Vector3::CrossProduct(Edge1, Edge2).Normalize(), this, this);

    return this;
}

const Surface* Parallelogram::IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const
{
    IntersectionData tempIntersectionData;
    if (IntersectRay(ray, &tempIntersectionData) == nullptr)
        return nullptr;

    intersectionData->push_back(tempIntersectionData);
    return this;
}