#include "NovahAdvancedMath.h"

using namespace Novah::AdvancedMath;

Cylinder::Cylinder(Vector3 position, Vector3 direction, float height, float radius)
    : Position(position), Direction(direction), Height(height), Radius(radius)
{

}

const Surface* Cylinder::IntersectRay(const Ray& ray, IntersectionData* intersectionData) const
{
    Vector3 rayPosition = ray.Position - Vector3::Dot(Direction, ray.Position) * Direction;
    Vector3 rayDirection = ray.Direction - Vector3::Dot(Direction, ray.Direction) * Direction;

    Vector3 cylinderPosition = Position - Vector3::Dot(Direction, Position) * Direction;

    float a = Vector3::Dot(rayDirection, rayDirection);
    float b = 2 * (Vector3::Dot(rayPosition, rayDirection) - Vector3::Dot(cylinderPosition, rayDirection));
    float c = -2 * Vector3::Dot(rayPosition, cylinderPosition) + Vector3::Dot(rayPosition, rayPosition) + Vector3::Dot(cylinderPosition, cylinderPosition) - Radius * Radius;

    float tMin = std::numeric_limits<float>().max();
    float tMax = std::numeric_limits<float>().max();

    bool isValid = true;

    Vector3 point;
    Vector3 positionToPoint;
    Vector3 pointProjectedOntoDirection;

    float radicand = b * b - 4 * a * c;
    if (radicand < 0.0f)
    {
        isValid = false;
        goto checkCaps;
    }

    float denominator = 2 * a;
    float negativeB = -b;

    tMin = (negativeB - sqrt(radicand)) / denominator;
    tMax = (negativeB + sqrt(radicand)) / denominator;

    if (tMax < 0.0f)
    {
        isValid = false;
        goto checkCaps;
    }

    point = ray.Position + tMin * ray.Direction;
    positionToPoint = point - Position;
    pointProjectedOntoDirection = Vector3::Project(positionToPoint, Direction);

    float cosAngle = Vector3::Dot(positionToPoint, Direction) / (positionToPoint.GetLength() * Direction.GetLength());
    if (Vector3::Dot(positionToPoint, Direction) <= 0.0f || pointProjectedOntoDirection.GetLength() > Height)
    {
        isValid = false;
        goto checkCaps;
    }

checkCaps:

    bool intersectionDataSet = false;

    IntersectionData bottomCapIntersectionData;
    if (IntersectBottomCap(ray, &bottomCapIntersectionData))
    {
        *intersectionData = bottomCapIntersectionData;
        intersectionDataSet = true;
    }

    IntersectionData topCapIntersectionData;
    if (IntersectTopCap(ray, &topCapIntersectionData) && (!intersectionDataSet || topCapIntersectionData.GetDistance() < intersectionData->GetDistance()))
    {
        *intersectionData = topCapIntersectionData;
        intersectionDataSet = true;
    }

    // Determine the point and normal of intersection.
    if (isValid && (!intersectionDataSet || tMin < intersectionData->GetDistance()))
    {
        Vector3 axisLine = Position + Direction * Height;
        Vector3 v1 = point - Position;
        Vector3 v2 = Vector3::Project(v1, Direction) + Position;

        Vector3 normal = (v1 - v2).Normalize();

        *intersectionData = IntersectionData(tMin, point, normal, this, this);
        intersectionDataSet = true;
    }

    if (intersectionDataSet)
        return this;

    return nullptr;
}

const Surface* Cylinder::IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const
{
    return nullptr;
}

bool Cylinder::IntersectBottomCap(const Ray& ray, IntersectionData* intersectionData) const
{
    Plane cap(-Direction, Position);

    if (cap.IntersectRay(ray, intersectionData) == nullptr)
        return false;

    if ((intersectionData->GetPoint() - Position).GetLengthSquared() > Radius * Radius)
        return false;

    return true;
}

bool Cylinder::IntersectTopCap(const Ray& ray, IntersectionData* intersectionData) const
{
    Plane cap(-Direction, Position + Height * Direction);

    if (cap.IntersectRay(ray, intersectionData) == nullptr)
        return false;

    if ((intersectionData->GetPoint() - (Position + Height * Direction)).GetLengthSquared() > Radius * Radius)
        return false;

    return true;
}