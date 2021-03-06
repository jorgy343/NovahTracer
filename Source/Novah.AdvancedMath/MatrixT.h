#pragma once

#include <math.h>
#include <algorithm>
#include "NovahAdvancedMath.h"

namespace Novah
{
    namespace AdvancedMath
    {
        template <typename T>
        class MatrixT
        {
        public:
            T
                M11, M12, M13, M14,
                M21, M22, M23, M24,
                M31, M32, M33, M34,
                M41, M42, M43, M44;

            MatrixT() = default;
            MatrixT(const MatrixT& other) = default;
            MatrixT& operator=(const MatrixT& other) = default;

            MatrixT(const Vector4T<T>& row1, const Vector4T<T>& row2, const Vector4T<T>& row3, const Vector4T<T>& row4)
                : MatrixT(
                    row1.X, row1.Y, row1.Z, row1.W,
                    row2.X, row2.Y, row2.Z, row2.W,
                    row3.X, row3.Y, row3.Z, row3.W,
                    row4.X, row4.Y, row4.Z, row4.W)
            {

            }

            explicit MatrixT(T scalar)
                : MatrixT(
                scalar, scalar, scalar, scalar,
                scalar, scalar, scalar, scalar,
                scalar, scalar, scalar, scalar,
                scalar, scalar, scalar, scalar)
            {

            }

            MatrixT(
                T m11, T m12, T m13, T m14,
                T m21, T m22, T m23, T m24,
                T m31, T m32, T m33, T m34,
                T m41, T m42, T m43, T m44)
                :
                    M11(m11), M12(m12), M13(m13), M14(m14),
                    M21(m21), M22(m22), M23(m23), M24(m24),
                    M31(m31), M32(m32), M33(m33), M34(m34),
                    M41(m41), M42(m42), M43(m43), M44(m44)
            {

            }

            // Instance members.
            T GetDeterminant() const
            {
                T temp1 = (M33 * M44) - (M34 * M43);
                T temp2 = (M32 * M44) - (M34 * M42);
                T temp3 = (M32 * M43) - (M33 * M42);
                T temp4 = (M31 * M44) - (M34 * M41);
                T temp5 = (M31 * M43) - (M33 * M41);
                T temp6 = (M31 * M42) - (M32 * M41);

                return ((((M11 * (((M22 * temp1) - (M23 * temp2)) + (M24 * temp3))) - (M12 * (((M21 * temp1) -
                    (M23 * temp4)) + (M24 * temp5)))) + (M13 * (((M21 * temp2) - (M22 * temp4)) + (M24 * temp6)))) -
                    (M14 * (((M21 * temp3) - (M22 * temp5)) + (M23 * temp6))));
            }

            MatrixT& Invert()
            {
                Invert(*this);
                return *this;
            }

            MatrixT& Negate()
            {
                Negate(*this);
                return *this;
            }

            MatrixT& Transpose()
            {
                Transpose(*this);
                return *this;
            }

            // Static members.
            static MatrixT Add(const MatrixT& left, const MatrixT& right)
            {
                MatrixT result;

                result.M11 = left.M11 + right.M11;
                result.M11 = left.M12 + right.M12;
                result.M11 = left.M13 + right.M13;
                result.M11 = left.M14 + right.M14;

                result.M21 = left.M21 + right.M21;
                result.M21 = left.M22 + right.M22;
                result.M21 = left.M23 + right.M23;
                result.M21 = left.M24 + right.M24;

                result.M31 = left.M31 + right.M31;
                result.M31 = left.M32 + right.M32;
                result.M31 = left.M33 + right.M33;
                result.M31 = left.M34 + right.M34;

                result.M41 = left.M41 + right.M41;
                result.M41 = left.M42 + right.M42;
                result.M41 = left.M43 + right.M43;
                result.M41 = left.M44 + right.M44;

                return result;
            }

            static MatrixT CreateScale(T scalar)
            {
                return CreateScale(scalar, scalar, scalar);
            }

            static MatrixT CreateScale(Vector3T<T> vector)
            {
                return CreateScale(vector.X, vector.Y, vector.Z);
            }

            static MatrixT CreateScale(T x, T y, T z)
            {
                MatrixT result = CreateIdentity();

                result.M11 = x;
                result.M22 = y;
                result.M33 = z;

                return result;
            }

            static MatrixT CreateIdentity()
            {
                MatrixT result;

                result.M12 = result.M13 = result.M14 =
                    result.M21 = result.M23 = result.M24 =
                    result.M31 = result.M32 = result.M34 =
                    result.M41 = result.M42 = result.M43 = (T)0;

                result.M11 = result.M22 = result.M33 = result.M44 = (T)1;
                return result;
            }

            static MatrixT CreateTranslation(T scalar)
            {
                return CreateTranslation(scalar, scalar, scalar);
            }

            static MatrixT CreateTranslation(Vector3T<T> vector)
            {
                return CreateTranslation(vector.X, vector.Y, vector.Z);
            }

            static MatrixT CreateTranslation(T x, T y, T z)
            {
                MatrixT result = CreateIdentity();

                result.M14 = x;
                result.M24 = y;
                result.M34 = z;

                return result;
            }

            static MatrixT CreateZero()
            {
                MatrixT result;

                result.M11 = result.M12 = result.M13 = result.M14 =
                    result.M21 = result.M22 = result.M23 = result.M24 =
                    result.M31 = result.M32 = result.M33 = result.M34 =
                    result.M41 = result.M42 = result.M43 = result.M44 = (T)0;

                return result;
            }

            static MatrixT EntrywiseProduct(const MatrixT& left, const MatrixT& right)
            {
                MatrixT result;

                result.M11 = left.M11 * right.M11;
                result.M12 = left.M12 * right.M12;
                result.M13 = left.M13 * right.M13;
                result.M14 = left.M14 * right.M14;

                result.M21 = left.M21 * right.M21;
                result.M22 = left.M22 * right.M22;
                result.M23 = left.M23 * right.M23;
                result.M24 = left.M24 * right.M24;

                result.M31 = left.M31 * right.M31;
                result.M32 = left.M32 * right.M32;
                result.M33 = left.M33 * right.M33;
                result.M34 = left.M34 * right.M34;

                result.M41 = left.M41 * right.M41;
                result.M42 = left.M42 * right.M42;
                result.M43 = left.M43 * right.M43;
                result.M44 = left.M44 * right.M44;
            }

            static bool Equals(const MatrixT& left, const MatrixT& right)
            {
                return
                    left.M11 == right.M11 &&
                    left.M12 == right.M12 &&
                    left.M13 == right.M13 &&
                    left.M14 == right.M14 &&

                    left.M21 == right.M21 &&
                    left.M22 == right.M22 &&
                    left.M23 == right.M23 &&
                    left.M24 == right.M24 &&

                    left.M31 == right.M31 &&
                    left.M32 == right.M32 &&
                    left.M33 == right.M33 &&
                    left.M34 == right.M34 &&

                    left.M41 == right.M41 &&
                    left.M42 == right.M42 &&
                    left.M43 == right.M43 &&
                    left.M44 == right.M44;
            }

            static MatrixT Invert(const MatrixT& matrix)
            {
                MatrixT result;

                T b0 = (matrix.M31 * matrix.M42) - (matrix.M32 * matrix.M41);
                T b1 = (matrix.M31 * matrix.M43) - (matrix.M33 * matrix.M41);
                T b2 = (matrix.M34 * matrix.M41) - (matrix.M31 * matrix.M44);
                T b3 = (matrix.M32 * matrix.M43) - (matrix.M33 * matrix.M42);
                T b4 = (matrix.M34 * matrix.M42) - (matrix.M32 * matrix.M44);
                T b5 = (matrix.M33 * matrix.M44) - (matrix.M34 * matrix.M43);

                T d11 = matrix.M22 * b5 + matrix.M23 * b4 + matrix.M24 * b3;
                T d12 = matrix.M21 * b5 + matrix.M23 * b2 + matrix.M24 * b1;
                T d13 = matrix.M21 * -b4 + matrix.M22 * b2 + matrix.M24 * b0;
                T d14 = matrix.M21 * b3 + matrix.M22 * -b1 + matrix.M23 * b0;

                T det = matrix.M11 * d11 - matrix.M12 * d12 + matrix.M13 * d13 - matrix.M14 * d14;
                if (abs(det) <= Epsilon)
                    return MatrixT((T)0);

                det = (T)1 / det;

                T a0 = (matrix.M11 * matrix.M22) - (matrix.M12 * matrix.M21);
                T a1 = (matrix.M11 * matrix.M23) - (matrix.M13 * matrix.M21);
                T a2 = (matrix.M14 * matrix.M21) - (matrix.M11 * matrix.M24);
                T a3 = (matrix.M12 * matrix.M23) - (matrix.M13 * matrix.M22);
                T a4 = (matrix.M14 * matrix.M22) - (matrix.M12 * matrix.M24);
                T a5 = (matrix.M13 * matrix.M24) - (matrix.M14 * matrix.M23);

                T d21 = matrix.M12 * b5 + matrix.M13 * b4 + matrix.M14 * b3;
                T d22 = matrix.M11 * b5 + matrix.M13 * b2 + matrix.M14 * b1;
                T d23 = matrix.M11 * -b4 + matrix.M12 * b2 + matrix.M14 * b0;
                T d24 = matrix.M11 * b3 + matrix.M12 * -b1 + matrix.M13 * b0;

                T d31 = matrix.M42 * a5 + matrix.M43 * a4 + matrix.M44 * a3;
                T d32 = matrix.M41 * a5 + matrix.M43 * a2 + matrix.M44 * a1;
                T d33 = matrix.M41 * -a4 + matrix.M42 * a2 + matrix.M44 * a0;
                T d34 = matrix.M41 * a3 + matrix.M42 * -a1 + matrix.M43 * a0;

                T d41 = matrix.M32 * a5 + matrix.M33 * a4 + matrix.M34 * a3;
                T d42 = matrix.M31 * a5 + matrix.M33 * a2 + matrix.M34 * a1;
                T d43 = matrix.M31 * -a4 + matrix.M32 * a2 + matrix.M34 * a0;
                T d44 = matrix.M31 * a3 + matrix.M32 * -a1 + matrix.M33 * a0;

                result.M11 = +d11 * det;
                result.M12 = -d21 * det;
                result.M13 = +d31 * det;
                result.M14 = -d41 * det;

                result.M21 = -d12 * det;
                result.M22 = +d22 * det;
                result.M23 = -d32 * det;
                result.M24 = +d42 * det;

                result.M31 = +d13 * det;
                result.M32 = -d23 * det;
                result.M33 = +d33 * det;
                result.M34 = -d43 * det;

                result.M41 = -d14 * det;
                result.M42 = +d24 * det;
                result.M43 = -d34 * det;
                result.M44 = +d44 * det;

                return result;
            }

            static MatrixT Lerp(const MatrixT& start, const MatrixT& end, T amount)
            {
                MatrixT result;

                result.M11 = start.M11 + (end.M11 - start.M11) * amount;
                result.M12 = start.M12 + (end.M12 - start.M12) * amount;
                result.M13 = start.M13 + (end.M13 - start.M13) * amount;
                result.M14 = start.M14 + (end.M14 - start.M14) * amount;
                result.M21 = start.M21 + (end.M21 - start.M21) * amount;
                result.M22 = start.M22 + (end.M22 - start.M22) * amount;
                result.M23 = start.M23 + (end.M23 - start.M23) * amount;
                result.M24 = start.M24 + (end.M24 - start.M24) * amount;
                result.M31 = start.M31 + (end.M31 - start.M31) * amount;
                result.M32 = start.M32 + (end.M32 - start.M32) * amount;
                result.M33 = start.M33 + (end.M33 - start.M33) * amount;
                result.M34 = start.M34 + (end.M34 - start.M34) * amount;
                result.M41 = start.M41 + (end.M41 - start.M41) * amount;
                result.M42 = start.M42 + (end.M42 - start.M42) * amount;
                result.M43 = start.M43 + (end.M43 - start.M43) * amount;
                result.M44 = start.M44 + (end.M44 - start.M44) * amount;

                return result;
            }

            static MatrixT Multiply(T left, const MatrixT& right)
            {
                MatrixT result;

                result.M11 = left * right.M11;
                result.M12 = left * right.M12;
                result.M13 = left * right.M13;
                result.M14 = left * right.M14;

                result.M21 = left * right.M21;
                result.M22 = left * right.M22;
                result.M23 = left * right.M23;
                result.M24 = left * right.M24;

                result.M31 = left * right.M31;
                result.M32 = left * right.M32;
                result.M33 = left * right.M33;
                result.M34 = left * right.M34;

                result.M41 = left * right.M41;
                result.M42 = left * right.M42;
                result.M43 = left * right.M43;
                result.M44 = left * right.M44;

                return result;
            }

            static MatrixT Multiply(const MatrixT& left, T right)
            {
                MatrixT result;

                result.M11 = left.M11 * right;
                result.M12 = left.M12 * right;
                result.M13 = left.M13 * right;
                result.M14 = left.M14 * right;

                result.M21 = left.M21 * right;
                result.M22 = left.M22 * right;
                result.M23 = left.M23 * right;
                result.M24 = left.M24 * right;

                result.M31 = left.M31 * right;
                result.M32 = left.M32 * right;
                result.M33 = left.M33 * right;
                result.M34 = left.M34 * right;

                result.M41 = left.M41 * right;
                result.M42 = left.M42 * right;
                result.M43 = left.M43 * right;
                result.M44 = left.M44 * right;

                return result;
            }

            static MatrixT Multiply(const MatrixT& left, const MatrixT& right)
            {
                MatrixT result;

                result.M11 = left.M11 * right.M11 + left.M12 * right.M21 + left.M13 * right.M31 + left.M14 * right.M41;
                result.M12 = left.M11 * right.M12 + left.M12 * right.M22 + left.M13 * right.M32 + left.M14 * right.M42;
                result.M13 = left.M11 * right.M13 + left.M12 * right.M23 + left.M13 * right.M33 + left.M14 * right.M43;
                result.M14 = left.M11 * right.M14 + left.M12 * right.M24 + left.M13 * right.M34 + left.M14 * right.M44;

                result.M21 = left.M21 * right.M11 + left.M22 * right.M21 + left.M23 * right.M31 + left.M24 * right.M41;
                result.M22 = left.M21 * right.M12 + left.M22 * right.M22 + left.M23 * right.M32 + left.M24 * right.M42;
                result.M23 = left.M21 * right.M13 + left.M22 * right.M23 + left.M23 * right.M33 + left.M24 * right.M43;
                result.M24 = left.M21 * right.M14 + left.M22 * right.M24 + left.M23 * right.M34 + left.M24 * right.M44;

                result.M31 = left.M31 * right.M11 + left.M32 * right.M21 + left.M33 * right.M31 + left.M34 * right.M41;
                result.M32 = left.M31 * right.M12 + left.M32 * right.M22 + left.M33 * right.M32 + left.M34 * right.M42;
                result.M33 = left.M31 * right.M13 + left.M32 * right.M23 + left.M33 * right.M33 + left.M34 * right.M43;
                result.M34 = left.M31 * right.M14 + left.M32 * right.M24 + left.M33 * right.M34 + left.M34 * right.M44;

                result.M41 = left.M41 * right.M11 + left.M42 * right.M21 + left.M43 * right.M31 + left.M44 * right.M41;
                result.M42 = left.M41 * right.M12 + left.M42 * right.M22 + left.M43 * right.M32 + left.M44 * right.M42;
                result.M43 = left.M41 * right.M13 + left.M42 * right.M23 + left.M43 * right.M33 + left.M44 * right.M43;
                result.M44 = left.M41 * right.M14 + left.M42 * right.M24 + left.M43 * right.M34 + left.M44 * right.M44;

                return result;
            }

            static Vector4T<T> Multiply(const MatrixT& matrix, T x, T y, T z, T w)
            {
                return Multiply(matrix, Vector4T<T>(x, y, z, w));
            }

            static Vector4T<T> Multiply(const MatrixT& matrix, const Vector2T<T>& vector, T z, T w)
            {
                return Multiply(matrix, Vector4T<T>(vector, z, w));
            }

            static Vector4T<T> Multiply(const MatrixT& matrix, const Vector3T<T>& vector, T w)
            {
                return Multiply(matrix, Vector4T<T>(vector, w));
            }

            static Vector4T<T> Multiply(const MatrixT& matrix, const Vector4T<T>& vector)
            {
                Vector4T<T> result;

                result.X = matrix.M11 * vector.X + matrix.M12 * vector.Y + matrix.M13 * vector.Z + matrix.M14 * vector.W;
                result.Y = matrix.M21 * vector.X + matrix.M22 * vector.Y + matrix.M23 * vector.Z + matrix.M24 * vector.W;
                result.Z = matrix.M31 * vector.X + matrix.M32 * vector.Y + matrix.M33 * vector.Z + matrix.M34 * vector.W;
                result.W = matrix.M41 * vector.X + matrix.M42 * vector.Y + matrix.M43 * vector.Z + matrix.M44 * vector.W;

                return result;
            }

            static MatrixT Negate(const MatrixT& matrix)
            {
                MatrixT result;

                result.M11 = -matrix.M11;
                result.M12 = -matrix.M12;
                result.M13 = -matrix.M13;
                result.M14 = -matrix.M14;

                result.M21 = -matrix.M21;
                result.M22 = -matrix.M22;
                result.M23 = -matrix.M23;
                result.M24 = -matrix.M24;

                result.M31 = -matrix.M31;
                result.M32 = -matrix.M32;
                result.M33 = -matrix.M33;
                result.M34 = -matrix.M34;

                result.M41 = -matrix.M41;
                result.M42 = -matrix.M42;
                result.M43 = -matrix.M43;
                result.M44 = -matrix.M44;

                return result;
            }

            static bool NotEquals(const MatrixT& left, const MatrixT& right)
            {
                return
                    left.M11 != right.M11 ||
                    left.M12 != right.M12 ||
                    left.M13 != right.M13 ||
                    left.M14 != right.M14 ||

                    left.M21 != right.M21 ||
                    left.M22 != right.M22 ||
                    left.M23 != right.M23 ||
                    left.M24 != right.M24 ||

                    left.M31 != right.M31 ||
                    left.M32 != right.M32 ||
                    left.M33 != right.M33 ||
                    left.M34 != right.M34 ||

                    left.M41 != right.M41 ||
                    left.M42 != right.M42 ||
                    left.M43 != right.M43 ||
                    left.M44 != right.M44;
            }

            static MatrixT Posit(const MatrixT& matrix)
            {
                MatrixT result;

                result.M11 = +matrix.M11;
                result.M12 = +matrix.M12;
                result.M13 = +matrix.M13;
                result.M14 = +matrix.M14;

                result.M21 = +matrix.M21;
                result.M22 = +matrix.M22;
                result.M23 = +matrix.M23;
                result.M24 = +matrix.M24;

                result.M31 = +matrix.M31;
                result.M32 = +matrix.M32;
                result.M33 = +matrix.M33;
                result.M34 = +matrix.M34;

                result.M41 = +matrix.M41;
                result.M42 = +matrix.M42;
                result.M43 = +matrix.M43;
                result.M44 = +matrix.M44;

                return result;
            }

            static MatrixT SmoothStep(const MatrixT& start, const MatrixT& end, T amount)
            {
                MatrixT result;

                amount = (amount > (T)1) ? (T)1 : ((amount < (T)0) ? (T)0 : amount);
                amount = (amount * amount) * ((T)3 - ((T)2 * amount));

                result.M11 = start.M11 + (end.M11 - start.M11) * amount;
                result.M12 = start.M12 + (end.M12 - start.M12) * amount;
                result.M13 = start.M13 + (end.M13 - start.M13) * amount;
                result.M14 = start.M14 + (end.M14 - start.M14) * amount;
                result.M21 = start.M21 + (end.M21 - start.M21) * amount;
                result.M22 = start.M22 + (end.M22 - start.M22) * amount;
                result.M23 = start.M23 + (end.M23 - start.M23) * amount;
                result.M24 = start.M24 + (end.M24 - start.M24) * amount;
                result.M31 = start.M31 + (end.M31 - start.M31) * amount;
                result.M32 = start.M32 + (end.M32 - start.M32) * amount;
                result.M33 = start.M33 + (end.M33 - start.M33) * amount;
                result.M34 = start.M34 + (end.M34 - start.M34) * amount;
                result.M41 = start.M41 + (end.M41 - start.M41) * amount;
                result.M42 = start.M42 + (end.M42 - start.M42) * amount;
                result.M43 = start.M43 + (end.M43 - start.M43) * amount;
                result.M44 = start.M44 + (end.M44 - start.M44) * amount;

                return result;
            }

            static MatrixT Subtract(const MatrixT& left, const MatrixT& right)
            {
                MatrixT result;

                result.M11 = left.M11 - right.M11;
                result.M11 = left.M12 - right.M12;
                result.M11 = left.M13 - right.M13;
                result.M11 = left.M14 - right.M14;

                result.M21 = left.M21 - right.M21;
                result.M21 = left.M22 - right.M22;
                result.M21 = left.M23 - right.M23;
                result.M21 = left.M24 - right.M24;

                result.M31 = left.M31 - right.M31;
                result.M31 = left.M32 - right.M32;
                result.M31 = left.M33 - right.M33;
                result.M31 = left.M34 - right.M34;

                result.M41 = left.M41 - right.M41;
                result.M41 = left.M42 - right.M42;
                result.M41 = left.M43 - right.M43;
                result.M41 = left.M44 - right.M44;

                return result;
            }

            static MatrixT Transpose(const MatrixT& matrix)
            {
                MatrixT result;

                result.M11 = matrix.M11;
                result.M12 = matrix.M21;
                result.M13 = matrix.M31;
                result.M14 = matrix.M41;

                result.M21 = matrix.M12;
                result.M22 = matrix.M22;
                result.M23 = matrix.M32;
                result.M24 = matrix.M42;

                result.M31 = matrix.M13;
                result.M32 = matrix.M23;
                result.M33 = matrix.M33;
                result.M34 = matrix.M43;

                result.M41 = matrix.M14;
                result.M42 = matrix.M24;
                result.M43 = matrix.M34;
                result.M44 = matrix.M44;

                return result;
            }

            // Operator members.
            bool operator==(const MatrixT& right) const
            {
                return Equals(*this, right);
            }

            bool operator!=(const MatrixT& right) const
            {
                return NotEquals(*this, right);
            }

            MatrixT operator+() const
            {
                return Posit(*this);
            }

            MatrixT operator-() const
            {
                return Negate(*this);
            }

            MatrixT operator+(const MatrixT& right) const
            {
                return Add(*this, right);
            }

            MatrixT operator-(const MatrixT& right) const
            {
                return Subtract(*this, right);
            }

            MatrixT operator*(T right) const
            {
                return Multiply(*this, right);
            }

            MatrixT operator*(const MatrixT& right) const
            {
                return Multiply(*this, right);
            }

            Vector4T<T> operator*(const Vector4T<T>& right) const
            {
                return Multiply(*this, right);
            }

            MatrixT& operator+=(const MatrixT& right)
            {
                *this = Add(*this, right);
                return *this;
            }

            MatrixT& operator-=(const MatrixT& right)
            {
                *this = Subtract(*this, right);
                return *this;
            }

            MatrixT& operator*=(T right)
            {
                *this = Multiply(*this, right);
                return *this;
            }
        };

        template <typename T>
        MatrixT<T> operator*(T left, const MatrixT<T>& right)
        {
            return right.Multiply(left, right);
        }
    }
}