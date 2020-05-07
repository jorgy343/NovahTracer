#include "Main.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Novah::AdvancedMath;

namespace NovahAdvancedMathNativeTests
{		
    TEST_CLASS(Color4TCompileTests)
    {
    public:
        TEST_METHOD(TestConstructors)
        {
            Color4T<int> color1;
            Color4T<int> color2(color1);
            Color4T<int> color3(1);
            Color4T<int> color4(1, 1, 1, 1);
        }

        TEST_METHOD(TestInstanceMethods)
        {
            Color4T<int> color;

            color.Abs();
            color.Clamp(color, color);
            color.GetLength();
            color.GetLengthSquared();
            color.Negate();
        }

        TEST_METHOD(TestStaticMethods)
        {
            Color4T<int> color;
            int scalar = 1;

            color.Abs(color);
            color.Add(color, color);
            color.Clamp(color, color, color);
            color.Divide(color, scalar);
            color.Divide(scalar, color);
            color.Lerp(color, color, scalar);
            color.Max(color, color);
            color.Min(color, color);
            color.Modulate(color, color);
            color.Multiply(color, scalar);
            color.Multiply(scalar, color);
            color.Negate(color);
            color.Posit(color);
            color.SmoothStep(color, color, scalar);
            color.Subtract(color, color);
        }

        TEST_METHOD(TestOperators)
        {
            Color4T<int> color;
            int scalar = 1;

            color.operator*(scalar);
            color.operator*=(scalar);
            color.operator+();
            color.operator+(color);
            color.operator+=(color);
            color.operator-();
            color.operator-(color);
            color.operator-=(color);
            color.operator/(scalar);
            color.operator=(color);
            color.operator==(color);
            color.operator!=(color);

            color.Red = 1;
            color.Green = 1;
            color.Blue = 1;
            color.Alpha = 1;

            scalar * color;
            scalar / color;
        }
    };
}