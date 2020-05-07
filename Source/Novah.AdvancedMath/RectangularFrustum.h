#pragma once

#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        class __declspec(align(16)) RectangularFrustum : public Surface
        {
        public:
            Plane Near, Far, Left, Right, Top, Bottom;

            RectangularFrustum() = default;
            RectangularFrustum(Plane near, Plane far, Plane left, Plane right, Plane top, Plane bottom);

            virtual const Surface* IntersectRay(const Ray& ray, IntersectionData* intersectionData) const override;
            virtual const Surface* IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const override;
        };
    }
}