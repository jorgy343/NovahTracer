#include "NovahAdvancedMath.h"
#include <limits>

using namespace Novah::AdvancedMath;

AxisAlignedRectangularBox::AxisAlignedRectangularBox(Vector3 minimum, Vector3 maximum)
    : Minimum(minimum), Maximum(maximum)
{

}

const Surface* AxisAlignedRectangularBox::IntersectRay(const Ray& ray, IntersectionData* intersectionData) const
{
    Vector3 dirfrac;
    dirfrac.X = 1.0f / ray.Direction.X;
    dirfrac.Y = 1.0f / ray.Direction.Y;
    dirfrac.Z = 1.0f / ray.Direction.Z;

    float t1 = (Minimum.X - ray.Position.X) * dirfrac.X;
    float t2 = (Maximum.X - ray.Position.X) * dirfrac.X;
    float t3 = (Minimum.Y - ray.Position.Y) * dirfrac.Y;
    float t4 = (Maximum.Y - ray.Position.Y) * dirfrac.Y;
    float t5 = (Minimum.Z - ray.Position.Z) * dirfrac.Z;
    float t6 = (Maximum.Z - ray.Position.Z) * dirfrac.Z;

    float tmax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

    // if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us.
    if (tmax < 0.0f)
        return nullptr;

    float tmin = fmax(fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6)), 0.0f);

    // if tmin > tmax, ray doesn't intersect AABB.
    if (tmin > tmax)
        return nullptr;

    // Calculate intersection data.
    Vector3 point = ray.Position + tmin * ray.Direction;
    Vector3 normal = CalculateNormal(point);

    *intersectionData = IntersectionData(tmin, point, normal, this, this);
    return this;
}

const Surface* AxisAlignedRectangularBox::IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const
{
    Vector3 dirfrac;
    dirfrac.X = 1.0f / ray.Direction.X;
    dirfrac.Y = 1.0f / ray.Direction.Y;
    dirfrac.Z = 1.0f / ray.Direction.Z;

    float t1 = (Minimum.X - ray.Position.X) * dirfrac.X;
    float t2 = (Maximum.X - ray.Position.X) * dirfrac.X;
    float t3 = (Minimum.Y - ray.Position.Y) * dirfrac.Y;
    float t4 = (Maximum.Y - ray.Position.Y) * dirfrac.Y;
    float t5 = (Minimum.Z - ray.Position.Z) * dirfrac.Z;
    float t6 = (Maximum.Z - ray.Position.Z) * dirfrac.Z;

    float tmax = fmin(fmin(fmax(t1, t2), fmax(t3, t4)), fmax(t5, t6));

    // if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us.
    if (tmax < 0.0f)
        return nullptr;

    float tmin = fmax(fmax(fmax(fmin(t1, t2), fmin(t3, t4)), fmin(t5, t6)), 0.0f);

    // if tmin > tmax, ray doesn't intersect AABB.
    if (tmin > tmax)
        return nullptr;

    // Calculate intersection data.
    Vector3 point = ray.Position + tmin * ray.Direction;
    Vector3 normal = CalculateNormal(point);

    intersectionData->push_back(IntersectionData(tmin, point, normal, this, this));

    point = ray.Position + tmax * ray.Direction;
    normal = CalculateNormal(point);

    intersectionData->push_back(IntersectionData(tmax, point, normal, this, this));
    return this;
}


Vector3 AxisAlignedRectangularBox::CalculateNormal(const Vector3& intersectionPoint) const
{
    Vector3 distanceMinimum = (intersectionPoint - Minimum).Abs();
    Vector3 distanceMaxmimum = (intersectionPoint - Maximum).Abs();

    // -X
    Vector3 normal = Vector3(-1.0f, 0.0f, 0.0f);
    float minimumDistance = distanceMinimum.X;

    // +X  
    if (distanceMaxmimum.X < minimumDistance)
    {
        normal = Vector3(1.0f, 0.0f, 0.0f);
        minimumDistance = distanceMaxmimum.X;
    }

    // -Y  
    if (distanceMinimum.Y < minimumDistance)
    {
        normal = Vector3(0.0f, -1.0f, 0.0f);
        minimumDistance = distanceMinimum.Y;
    }

    // +Y  
    if (distanceMaxmimum.Y < minimumDistance)
    {
        normal = Vector3(0.0f, 1.0f, 0.0f);
        minimumDistance = distanceMaxmimum.Y;
    }

    // -Z  
    if (distanceMinimum.Z < minimumDistance)
    {
        normal = Vector3(0.0f, 0.0f, -1.0f);
        minimumDistance = distanceMinimum.Z;
    }

    // +Z  
    if (distanceMaxmimum.Z < minimumDistance)
        normal = Vector3(0.0f, 0.0f, 1.0f);

    return normal;
}