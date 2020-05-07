#pragma once

#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        class __declspec(align(16)) Cylinder : public Surface
        {
        public:
            Vector3 Position, Direction;
            float Height, Radius;

            Cylinder() = default;
            Cylinder(Vector3 center, Vector3 direction, float height, float radius);

            virtual const Surface* IntersectRay(const Ray& ray, IntersectionData* intersectionData) const override;
            virtual const Surface* IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const override;

        private:
            bool IntersectBottomCap(const Ray& ray, IntersectionData* intersectionData) const;
            bool IntersectTopCap(const Ray& ray, IntersectionData* intersectionData) const;
        };
    }
}