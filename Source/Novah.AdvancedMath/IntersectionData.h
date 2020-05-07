#pragma once

#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        class Surface;

        class IntersectionData
        {
        private:
            float _distance;
            Vector3 _point, _normal;
            const Surface* _collisionSurface;
            const Surface* _detailedSurface;

        public:
            IntersectionData() = default;
            IntersectionData(float distance, const Vector3& point, const Vector3& normal, const Surface* collisionSurface, const Surface* detailedSurface);

            float GetDistance() const;
            void SetDistance(float distance);

            Vector3 GetPoint() const;
            void SetPoint(const Vector3& point);

            Vector3 GetNormal() const;
            void SetNormal(const Vector3& normal);

            const Surface* GetCollisionSurface() const;
            void SetCollisionSurface(const Surface* collisionSurface);

            const Surface* GetDetailedSurface() const;
            void SetDetailedSurface(const Surface* detailedSurface);
        };
    }
}