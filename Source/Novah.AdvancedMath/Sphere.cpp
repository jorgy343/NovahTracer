﻿#include "NovahAdvancedMath.h"

using namespace Novah::AdvancedMath;

Sphere::Sphere(Vector3 position, float radius)
    : Position(position), Radius(radius)
{

}

const Surface* Sphere::IntersectRay(const Ray& ray, IntersectionData* intersectionData) const
{
    // ‖x − c‖² = r²                    Equation of sphere
    // x = s + td                       Equation of ray
    // 
    // ‖s + td - c‖² = r²               Substitute equation of ray into equation of sphere
    // v ≝ s − c
    // ‖v + td‖² = r²
    // v² + 2t(v⋅d) + t²d² = r²         Expand binomial
    // t²d² + 2t(v⋅d) + v² - r² = 0
    // 
    // a = d², b = 2(v⋅d), c = v² - r²
    // (-b ± √(b² - 4ac)) / (2a)        Quadratic equation.
    // 
    // t = (-2(v⋅d) ± √((2(v⋅d))² - 4d²(v² - r²))) / (2d²)
    // t = (-(v⋅d) ± √((v⋅d)² - d²(v² - r²))) / d²
    // 
    // Discriminant is
    // (v⋅d)² - d²(v² - r²)
    // 
    // Entrance of intersection
    // (-(v⋅d) + √((v⋅d)² - d²(v² - r²))) / d²
    // 
    // Exit of intersection
    // (-(v⋅d) - √((v⋅d)² - d²(v² - r²))) / d²

    Vector3 v = ray.Position - Position;
    float vDotd = Vector3::Dot(v, ray.Direction);
    float vDotdSquared = vDotd * vDotd;

    float dSquared = Vector3::Dot(ray.Direction, ray.Direction);
    float vSquared = Vector3::Dot(v, v);
    float rSquared = Radius * Radius;

    float discriminant = vDotdSquared - dSquared * (vSquared - rSquared);
    if (discriminant < Epsilon)
        return nullptr;

    float discriminantSquareRoot = sqrt(discriminant);
    float vDotdNegative = -vDotd;

    float exitDistance = (vDotdNegative + discriminantSquareRoot) / dSquared;
    if (exitDistance < Epsilon)
        return nullptr;

    float entranceDistance = fmax((vDotdNegative - discriminantSquareRoot) / dSquared, 0.0f);

    Vector3 point = ray.Position + entranceDistance * ray.Direction;
    Vector3 normal = (point - Position).Normalize();

    *intersectionData = IntersectionData(entranceDistance, point, normal, this, this);
    return this;
}

const Surface* Sphere::IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const
{
    Vector3 v = ray.Position - Position;
    float vDotd = Vector3::Dot(v, ray.Direction);
    float vDotdSquared = vDotd * vDotd;

    float dSquared = Vector3::Dot(ray.Direction, ray.Direction);
    float vSquared = Vector3::Dot(v, v);
    float rSquared = Radius * Radius;

    float discriminant = vDotdSquared - dSquared * (vSquared - rSquared);
    if (discriminant < Epsilon)
        return nullptr;

    float discriminantSquareRoot = sqrt(discriminant);
    float vDotdNegative = -vDotd;

    
    float exitDistance = (vDotdNegative + discriminantSquareRoot) / dSquared;
    if (exitDistance < Epsilon)
        return nullptr;

    float entranceDistance = fmax((vDotdNegative - discriminantSquareRoot) / dSquared, 0.0f);

    // Create hit records.
    Vector3 entrancePoint = ray.Position + entranceDistance * ray.Direction;
    Vector3 entranceNormal = (entrancePoint - Position).Normalize();

    Vector3 exitPoint = ray.Position + exitDistance * ray.Direction;
    Vector3 exitNormal = (exitPoint - Position).Normalize();

    intersectionData->push_back(IntersectionData(entranceDistance, entrancePoint, entranceNormal, this, this));
    intersectionData->push_back(IntersectionData(exitDistance, exitPoint, exitNormal, this, this));

    return this;
}