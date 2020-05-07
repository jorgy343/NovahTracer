#pragma once

#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        class __declspec(align(16)) TransformedSurface : public Surface
        {
        private:
            const Surface* _surface;
            Matrix _inversedTransform;
            Matrix _inverseTransposedTransform;

        public:
            TransformedSurface(const Surface* surface, const Matrix& transform);

            virtual const Surface* IntersectRay(const Ray& ray, IntersectionData* intersectionData) const override;
            virtual const Surface* IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const override;

            const Surface* GetSurface() const;
        };
    }
}