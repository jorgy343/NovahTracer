#pragma once

#include <math.h>
#include <algorithm>
#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        template <typename T>
        class QuaternionT
        {
        public:
            T X, Y, Z, W;

            QuaternionT() = default;
            QuaternionT(const QuaternionT& other) = default;
            QuaternionT& operator=(const QuaternionT& other) = default;

            QuaternionT(const Vector4T<T>& vector)
                : QuaternionT(X, Y, Z, W)
            {

            }

            explicit QuaternionT(T scalar)
                : QuaternionT(scalar, scalar, scalar, scalar)
            {

            }

            QuaternionT(T x, T y, T z, T w)
                : X(x), Y(y), Z(z), W(w)
            {

            }

            // Instance members.
            void Conjugate()
            {
                X = -X;
                Y = -Y;
                Z = -Z;
            }

            T GetAngle() const
            {
                T length = (X * X) + (Y * Y) + (Z * Z);
                return (T)((T)2 * acos(W));
            }

            Vector3T GetAxis() const
            {
                T length = (X * X) + (Y * Y) + (Z * Z);
                T inverse = (T)1 / length;

                return Vector3T(X * inverse, Y * inverse, Z * inverse);
            }

            T GetLength() const
            {
                return (T)sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));
            }

            T GetLengthSquared() const
            {
                return (X * X) + (Y * Y) + (Z * Z) + (W * W);
            }

            // Static members.
            static QuaternionT Add(const QuaternionT& left, const QuaternionT& right)
            {
                return QuaternionT(left.X + right.X, left.Y + right.Y, left.Z + right.Z, left.W + right.W);
            }

            static QuaternionT Subtract(const QuaternionT& left, const QuaternionT& right)
            {
                return QuaternionT(left.X - right.X, left.Y - right.Y, left.Z - right.Z, left.W - right.W);
            }

            static QuaternionT Multiply(const QuaternionT& left, const QuaternionT& right)
            {
                QuaternionT result;

                T lx = left.X;
                T ly = left.Y;
                T lz = left.Z;
                T lw = left.W;
                T rx = right.X;
                T ry = right.Y;
                T rz = right.Z;
                T rw = right.W;

                result.X = (rx * lw + lx * rw + ry * lz) - (rz * ly);
                result.Y = (ry * lw + ly * rw + rz * lx) - (rx * lz);
                result.Z = (rz * lw + lz * rw + rx * ly) - (ry * lx);
                result.W = (rw * lw) - (rx * lx + ry * ly + rz * lz);

                return result;
            }

            static QuaternionT CreateIdentity()
            {
                return QuaternionT((T)0, (T)0, (T)0, (T)1);
            }
        };
    }
}