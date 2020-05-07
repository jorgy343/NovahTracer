#pragma once

#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        class __declspec(align(16)) Ray : public Surface
        {
        public:
            Vector3 Position, Direction;

            Ray() = default;
            Ray(Vector3 position, Vector3 direction);

            virtual const Surface* IntersectRay(const Ray& ray, IntersectionData* intersectionData) const override;
            virtual const Surface* IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const override;
        };
    }
}