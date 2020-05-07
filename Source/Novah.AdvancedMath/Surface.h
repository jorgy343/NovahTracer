#pragma once

#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        class Ray;

        class Surface
        {
        public:
            virtual const Surface* IntersectRay(const Ray& ray, IntersectionData* intersectionData) const = 0;
            virtual const Surface* IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const = 0;
        };
    }
}