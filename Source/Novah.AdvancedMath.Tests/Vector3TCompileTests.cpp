#include "Main.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Novah::AdvancedMath;

namespace NovahAdvancedMathNativeTests
{		
    TEST_CLASS(Vector3TCompileTests)
    {
    public:
        TEST_METHOD(TestConstructors)
        {
            Vector3T<int> vector1;
            Vector3T<int> vector2(vector1);
            Vector3T<int> vector3(1);
            Vector3T<int> vector4(1, 1, 1);
            Vector3T<int> vector5(Vector2T<int>(1, 1), 1);
        }

        TEST_METHOD(TestInstanceMethods)
        {
            Vector3T<int> vector;

            vector.Abs();
            vector.Clamp(vector, vector);
            vector.GetLength();
            vector.GetLengthSquared();
            vector.Negate();
            vector.Normalize();
        }

        TEST_METHOD(TestStaticMethods)
        {
            Vector3T<int> vector;
            int scalar = 1;

            vector.Abs(vector);
            vector.Add(vector, vector);
            vector.Barycentric(vector, vector, vector, scalar, scalar);
            vector.CatmullRom(vector, vector, vector, vector, scalar);
            vector.Clamp(vector, vector, vector);
            vector.CrossProduct(vector, vector);
            vector.Distance(vector, vector);
            vector.DistanceSquared(vector, vector);
            vector.Divide(vector, scalar);
            vector.Divide(scalar, vector);
            vector.Dot(vector, vector);
            vector.GetLength(vector);
            vector.GetLengthSquared(vector);
            vector.Hermite(vector, vector, vector, vector, scalar);
            vector.Lerp(vector, vector, scalar);
            vector.Max(vector, vector);
            vector.Min(vector, vector);
            vector.Modulate(vector, vector);
            vector.Multiply(vector, scalar);
            vector.Multiply(scalar, vector);
            vector.Negate(vector);
            vector.Normalize(vector);
            vector.Posit(vector);
            vector.Reflect(vector, vector);
            vector.SmoothStep(vector, vector, scalar);
            vector.Subtract(vector, vector);
        }

        TEST_METHOD(TestOperators)
        {
            Vector3T<int> vector;
            int scalar = 1;

            vector.operator*(scalar);
            vector.operator*=(scalar);
            vector.operator+();
            vector.operator+(vector);
            vector.operator+=(vector);
            vector.operator-();
            vector.operator-(vector);
            vector.operator-=(vector);
            vector.operator/(scalar);
            vector.operator=(vector);
            vector.operator==(vector);
            vector.operator!=(vector);

            vector.X = 1;
            vector.Y = 1;
            vector.Z = 1;

            scalar * vector;
            scalar / vector;
        }
    };
}