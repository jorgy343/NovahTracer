#pragma once

#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        class __declspec(align(16)) Plane : public Surface
        {
        public:
            Vector3 Normal;
            float D;

            Plane() = default;
            Plane(Vector3 normal, float d);
            Plane(Vector3 normal, Vector3 point);

            virtual const Surface* IntersectRay(const Ray& ray, IntersectionData* intersectionData) const override;
            virtual const Surface* IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const override;
        };
    }
}