#pragma once

#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        class __declspec(align(16)) Quadric : public Surface
        {
        public:
            float A, B, C, D, E, F, G, H, I, J;

            Quadric() = default;
            Quadric(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j);

            virtual const Surface* IntersectRay(const Ray& ray, IntersectionData* intersectionData) const override;
            virtual const Surface* IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const override;
        };
    }
}