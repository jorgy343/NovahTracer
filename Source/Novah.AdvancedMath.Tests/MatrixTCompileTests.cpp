#include "Main.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Novah::AdvancedMath;

namespace NovahAdvancedMathNativeTests
{		
    TEST_CLASS(Vector4TCompileTests)
    {
    public:
        TEST_METHOD(TestConstructors)
        {
            Vector4T<int> vector;

            MatrixT<int> matrix1;
            MatrixT<int> matrix2(matrix1);
            MatrixT<int> matrix3(1);
            MatrixT<int> matrix4(vector, vector, vector, vector);
            MatrixT<int> matrix5(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
        }

        TEST_METHOD(TestInstanceMethods)
        {
            MatrixT<int> matrix;

            matrix.GetDeterminant();
            matrix.Invert();
            matrix.Negate();
            matrix.Transpose();
        }

        TEST_METHOD(TestStaticMethods)
        {
            MatrixT<int> matrix;
            Vector3T<int> vector3;
            Vector4T<int> vector4;
            int scalar = 1;

            matrix.Add(matrix, matrix);
            matrix.CreateScale(scalar);
            matrix.CreateScale(vector3);
            matrix.CreateScale(scalar, scalar, scalar);
            matrix.Invert(matrix);
            matrix.Lerp(matrix, matrix, scalar);
            matrix.Multiply(1, matrix);
            matrix.Multiply(matrix, 1);
            matrix.Multiply(matrix, matrix);
            matrix.Multiply(matrix, vector4);
            matrix.Multiply(matrix, vector3, scalar);
            matrix.Negate(matrix);
            matrix.SmoothStep(matrix, matrix, scalar);
            matrix.Subtract(matrix, matrix);
            matrix.Transpose(matrix);
        }

        TEST_METHOD(TestOperators)
        {
            MatrixT<int> matrix;
            Vector4T<int> vector4;
            int scalar = 1;

            matrix.operator=(matrix);
            matrix.operator==(matrix);
            matrix.operator!=(matrix);
            matrix.operator+();
            matrix.operator-();
            matrix.operator+(matrix);
            matrix.operator-(matrix);
            matrix.operator*(scalar);
            matrix.operator*(matrix);
            matrix.operator+=(matrix);
            matrix.operator-=(matrix);
            matrix.operator*=(scalar);
            matrix.operator*=(matrix);

            scalar * matrix;
            matrix * vector4;
            //vector4 * matrix;
        }
    };
}