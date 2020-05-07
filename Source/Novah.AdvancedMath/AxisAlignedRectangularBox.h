#pragma once

#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        class __declspec(align(16)) AxisAlignedRectangularBox : public Surface
        {
        public:
            Vector3 Minimum, Maximum;

            AxisAlignedRectangularBox() = default;
            AxisAlignedRectangularBox(Vector3 minimum, Vector3 maximum);

            virtual const Surface* IntersectRay(const Ray& ray, IntersectionData* intersectionData) const override;
            virtual const Surface* IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const override;

        private:
            Vector3 CalculateNormal(const Vector3& intersectionPoint) const;
        };
    }
}