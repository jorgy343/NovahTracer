#pragma once

#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        class CsgSurface : public Surface
        {
        private:
            const Surface* _leftSurface;
            const Surface* _rightSurface;
            CsgOperation _operation;

        public:
            CsgSurface(const Surface* leftSurface, const Surface* rightSurface, CsgOperation operation);

            virtual const Surface* IntersectRay(const Ray& ray, IntersectionData* intersectionData) const override;
            virtual const Surface* IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const override;

            const Surface* GetLeftSurface() const;
            const Surface* GetRightSurface() const;
            CsgOperation GetOperation() const;
        };
    }
}