#include "WindowsInclude.h"
#include "Size.h"
#include "Exception.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(SizeTest)
	{
	public:
		SizeTest()
		{
		}

		TEST_METHOD(DefaultConstructor)
		{
			Size size;
			Assert.AreEqual(0, size.cx);
			Assert.AreEqual(0, size.cy);
		}

		TEST_METHOD(MemberwiseConstructor)
		{
			const auto width = 1;
			const auto height = 2;
			Size size{ width, height };
			Assert.AreEqual(width, size.cx);
			Assert.AreEqual(height, size.cy);
		}

		TEST_METHOD(SizeConstructor)
		{
			const auto width = 1;
			const auto height = 2;
			SIZE value{ width, height };
			Size size{ value };
			Assert.AreEqual(width, size.cx);
			Assert.AreEqual(height, size.cy);
		}

		TEST_METHOD(PointConstructor)
		{
			const auto left = 1;
			const auto top = 2;
			POINT value{ left, top };
			Size size{ value };
			Assert.AreEqual(left, size.cx);
			Assert.AreEqual(top, size.cy);
		}

		TEST_METHOD(PackConstructor)
		{
			const auto width = 1;
			const auto height = 2;
			Size size{ MAKEWPARAM(width, height) };
			Assert.AreEqual(width, size.cx);
			Assert.AreEqual(height, size.cy);
		}

		TEST_METHOD(PackConstructor2)
		{
			const auto width = 1;
			const auto height = 2;
			Size size{ MAKELPARAM(width, height) };
			Assert.AreEqual(width, size.cx);
			Assert.AreEqual(height, size.cy);
		}

		TEST_METHOD(Set)
		{
			const auto width = 1;
			const auto height = 2;
			Size size;
			size.Set(width, height);
			Assert.AreEqual(width, size.cx);
			Assert.AreEqual(height, size.cy);
		}

		TEST_METHOD(Pack)
		{
			const auto width = 1;
			const auto height = 2;
			Size size{ width, height };
			auto result = size.Pack();
			Assert.AreEqual(width, LOWORD(result));
			Assert.AreEqual(height, HIWORD(result));
		}

		TEST_METHOD(GetWidth)
		{
			const auto width = 1;
			Size size{ width, 0 };
			Assert.AreEqual(width, size.GetWidth());
		}

		TEST_METHOD(GetHeight)
		{
			const auto height = 1;
			Size size{ 0, height };
			Assert.AreEqual(height, size.GetHeight());
		}

		TEST_METHOD(SetWidth)
		{
			const auto width = 1;
			Size size;
			size.SetWidth(width);
			Assert.AreEqual(width, size.cx);
		}

		TEST_METHOD(SetHeight)
		{
			const auto height = 1;
			Size size;
			size.SetHeight(height);
			Assert.AreEqual(height, size.cy);
		}

		TEST_METHOD(Plus)
		{
			const auto width1 = 1;
			const auto width2 = 2;
			const auto height1 = 3;
			const auto height2 = 4;
			Size size1{ width1, height1 };
			Size size2{ width2, height2 };
			auto result = size1 + size2;
			Assert.AreEqual(width1 + width2, result.cx);
			Assert.AreEqual(height1 + height2, result.cy);
		}

		TEST_METHOD(PlusEquals)
		{
			const auto width1 = 1;
			const auto width2 = 2;
			const auto height1 = 3;
			const auto height2 = 4;
			Size size1{ width1, height1 };
			Size size2{ width2, height2 };
			auto& result = size1 += size2;
			Assert.AreEqual(&size1, &result);
			Assert.AreEqual(width1 + width2, result.cx);
			Assert.AreEqual(height1 + height2, result.cy);
		}

		TEST_METHOD(Minus)
		{
			const auto width1 = 1;
			const auto width2 = 2;
			const auto height1 = 3;
			const auto height2 = 4;
			Size size1{ width1, height1 };
			Size size2{ width2, height2 };
			auto result = size1 - size2;
			Assert.AreEqual(width1 - width2, result.cx);
			Assert.AreEqual(height1 - height2, result.cy);
		}

		TEST_METHOD(MinusEquals)
		{
			const auto width1 = 1;
			const auto width2 = 2;
			const auto height1 = 3;
			const auto height2 = 4;
			Size size1{ width1, height1 };
			Size size2{ width2, height2 };
			auto& result = size1 -= size2;
			Assert.AreEqual(&size1, &result);
			Assert.AreEqual(width1 - width2, result.cx);
			Assert.AreEqual(height1 - height2, result.cy);
		}

		TEST_METHOD(ScalarMultiply)
		{
			const auto width = 2;
			const auto height = 3;
			const auto multiplier = 4;
			Size size{ width, height };
			auto result = size * multiplier;
			Assert.AreEqual(width * multiplier, result.cx);
			Assert.AreEqual(height * multiplier, result.cy);
		}

		TEST_METHOD(ScalarMultiplyEquals)
		{
			const auto width = 2;
			const auto height = 3;
			const auto multiplier = 4;
			Size size{ width, height };
			auto& result = size *= multiplier;
			Assert.AreEqual(&size, &result);
			Assert.AreEqual(width * multiplier, result.cx);
			Assert.AreEqual(height * multiplier, result.cy);
		}

		TEST_METHOD(ScalarDivide_DivideByZero)
		{
			try
			{
				Size{} / 0;
				Assert.Fail();
			}
			catch (const Exception& exception)
			{
				Assert.AreEqual(std::string{ "divisor" }, exception.GetLocation());
				Assert.AreEqual(0, exception.GetErrorCode());
				Assert.AreEqual(std::string{ "Divide by zero." }, exception.GetDescription());
			}
		}

		TEST_METHOD(ScalarDivide_IntegerDivision)
		{
			const auto divisor = 5;
			const auto width = divisor + 1;
			const auto height = 2 * divisor - 1;
			Size size{ width, height };
			auto result = size / divisor;
			Assert.AreEqual(1, result.cx);
			Assert.AreEqual(1, result.cy);
		}

		TEST_METHOD(ScalarDivide_Valid)
		{
			const auto width = 1;
			const auto height = 2;
			const auto divisor = 3;
			Size size{ width * divisor, height * divisor };
			auto result = size / divisor;
			Assert.AreEqual(width, result.cx);
			Assert.AreEqual(height, result.cy);
		}

		TEST_METHOD(ScalarDivideEquals)
		{
			const auto width = 1;
			const auto height = 2;
			const auto divisor = 3;
			Size size{ width * divisor, height * divisor };
			auto& result = size /= divisor;
			Assert.AreEqual(&size, &result);
			Assert.AreEqual(width, result.cx);
			Assert.AreEqual(height, result.cy);
		}

		TEST_METHOD(EqualTo_DifferentWidth)
		{
			Assert.IsFalse(Size{ 1, 2 } == Size{ 3, 2 });
		}

		TEST_METHOD(EqualTo_DifferentHeight)
		{
			Assert.IsFalse(Size{ 1, 2 } == Size{ 1, 3 });
		}

		TEST_METHOD(EqualTo_Equal)
		{
			Assert.IsTrue(Size{ 1, 2 } == Size{ 1, 2 });
		}

		TEST_METHOD(NotEqualTo_DifferentWidth)
		{
			Assert.IsTrue(Size{ 1, 2 } != Size{ 3, 2 });
		}

		TEST_METHOD(NotEqualTo_DifferentHeight)
		{
			Assert.IsTrue(Size{ 1, 2 } != Size{ 1, 3 });
		}

		TEST_METHOD(NotEqualTo_Equal)
		{
			Assert.IsFalse(Size{ 1, 2 } != Size{ 1, 2 });
		}
	};
}

