#pragma once

#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        class __declspec(align(16)) BoundingVolume : virtual public Surface
        {
        private:
            const Surface* _surface;

        public:
            BoundingVolume(const BoundingVolume& boundingVolume);
            BoundingVolume(const Surface* surface);

            const Surface* GetSurface() const;
        };
    }
}