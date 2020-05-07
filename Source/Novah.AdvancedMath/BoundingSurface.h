#pragma once

#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        class BoundingSurface : public Surface
        {
        private:
            const Surface* _bounder;
            const Surface* _surface;

        public:
            BoundingSurface(const Surface* bounder, const Surface* surface);

            virtual const Surface* IntersectRay(const Ray& ray, IntersectionData* intersectionData) const override;
            virtual const Surface* IntersectRay(const Ray& ray, std::vector<IntersectionData>* intersectionData) const override;

            const Surface* GetBounder() const;
            const Surface* GetSurface() const;
        };
    }
}