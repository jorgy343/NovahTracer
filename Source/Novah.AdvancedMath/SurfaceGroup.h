#pragma once

#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        class SurfaceGroup : public Surface
        {
        private:
            const std::vector<const Surface*>* _surfaces;

        public:
            SurfaceGroup(const std::vector<const Surface*>* surfaces);

            virtual const Surface* IntersectRay(const Ray& ray, IntersectionData* intersectionData) const override;
            virtual const Surface* IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const override;
        };
    }
}