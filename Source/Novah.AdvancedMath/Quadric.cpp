#include "NovahAdvancedMath.h"

using namespace Novah::AdvancedMath;

Quadric::Quadric(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j)
    : A(a), B(b), C(c), D(d), E(e), F(f), G(g), H(h), I(i), J(j)
{

}

const Surface* Quadric::IntersectRay(const Ray& ray, IntersectionData* intersectionData) const
{
    Matrix Q(
        A, B, C, D,
        B, E, F, G,
        C, F, H, I,
        D, G, I, J);

    Vector4 s(ray.Position.X, ray.Position.Y, ray.Position.Z, 1.0f);
    Vector4 d(ray.Direction.X, ray.Direction.Y, ray.Direction.Z, 0.0f);

    Vector4 qs = Q * s;
    Vector4 qd = Q * d;

    float a = Vector4::Dot(d, qd);
    float b = Vector4::Dot(s, qd) + Vector4::Dot(d, qs);
    float c = Vector4::Dot(s, qs);

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant < 0.0f)
        return nullptr;

    float distance = (-b - sqrt(discriminant)) / (2.0f * a);
    if (distance < 0.0f)
        return nullptr;

    Vector3 point = ray.Position + distance * ray.Direction;
    Vector4 point4(point.X, point.Y, point.Z, 1.0f);

    Vector4 normal4 = Q * point4;
    Vector3 normal = Vector3(normal4.X, normal4.Y, normal4.Z).Normalize();

    *intersectionData = IntersectionData(distance, point, normal, this, this);
    return this;
}

const Surface* Quadric::IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const
{
    Matrix Q(
        A, B, C, D,
        B, E, F, G,
        C, F, H, I,
        D, G, I, J);

    Vector4 s(ray.Position.X, ray.Position.Y, ray.Position.Z, 1.0f);
    Vector4 d(ray.Direction.X, ray.Direction.Y, ray.Direction.Z, 0.0f);

    Vector4 qs = Q * s;
    Vector4 qd = Q * d;

    float a = Vector4::Dot(d, qd);
    float b = Vector4::Dot(s, qd) + Vector4::Dot(d, qs);
    float c = Vector4::Dot(s, qs);

    float discriminant = b * b - 4.0f * a * c;
    if (discriminant < 0.0f)
        return nullptr;

    // TODO: Pull out common factors for near and far distance.
    float farDistance = (-b + sqrt(discriminant)) / (2.0f * a);
    if (farDistance < 0.0f)
        return nullptr;

    float nearDistance = (-b - sqrt(discriminant)) / (2.0f * a);

    {
        Vector3 point = ray.Position + nearDistance * ray.Direction;
        Vector4 point4(point.X, point.Y, point.Z, 1.0f); // Should w be 0 or 1?

        Vector4 normal4 = Q * point4;
        Vector3 normal = Vector3(normal4.X, normal4.Y, normal4.Z).Normalize();

        intersectionData->push_back(IntersectionData(nearDistance, point, normal, this, this));
    }

    {
        Vector3 point = ray.Position + farDistance * ray.Direction;
        Vector4 point4(point.X, point.Y, point.Z, 1.0f); // Should w be 0 or 1?

        Vector4 normal4 = Q * point4;
        Vector3 normal = Vector3(normal4.X, normal4.Y, normal4.Z).Normalize();

        intersectionData->push_back(IntersectionData(farDistance, point, normal, this, this));
    }

    return this;
}