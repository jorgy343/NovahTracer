#pragma once

#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        class __declspec(align(16)) Sphere : public Surface
        {
        public:
            Vector3 Position;
            float Radius;

            Sphere() = default;
            Sphere(Vector3 position, float radius);

            virtual const Surface* IntersectRay(const Ray& ray, IntersectionData* intersectionData) const override;
            virtual const Surface* IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const override;
        };
    }
}