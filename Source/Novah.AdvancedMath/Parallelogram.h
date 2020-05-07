#pragma once

#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        class __declspec(align(16)) Parallelogram : public Surface
        {
        public:
            Vector3 Corner, Edge1, Edge2;

            Parallelogram() = default;
            Parallelogram(const Vector3& corner, const Vector3& edge1, const Vector3& edge2);

            virtual const Surface* IntersectRay(const Ray& ray, IntersectionData* intersectionData) const override;
            virtual const Surface* IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const override;
        };
    }
}