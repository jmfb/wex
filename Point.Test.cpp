#include "WindowsInclude.h"
#include "Point.h"
#include "Exception.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(PointTest)
	{
	public:
		PointTest()
		{
		}

		TEST_METHOD(UseDefaultValue)
		{
			Assert.AreEqual(CW_USEDEFAULT, Point::UseDefault.x);
			Assert.AreEqual(CW_USEDEFAULT, Point::UseDefault.y);
		}

		TEST_METHOD(TopLeftValue)
		{
			Assert.AreEqual(0, Point::TopLeft.x);
			Assert.AreEqual(0, Point::TopLeft.y);
		}

		TEST_METHOD(DefaultConstructor)
		{
			Point point;
			Assert.AreEqual(0, point.x);
			Assert.AreEqual(0, point.y);
		}

		TEST_METHOD(MemberwiseConstructor)
		{
			const auto left = 1;
			const auto top = 2;
			Point point{ left, top };
			Assert.AreEqual(left, point.x);
			Assert.AreEqual(top, point.y);
		}

		TEST_METHOD(PointConstructor)
		{
			const auto left = 1;
			const auto top = 2;
			POINT value{ left, top };
			Point point{ value };
			Assert.AreEqual(left, point.x);
			Assert.AreEqual(top, point.y);
		}

		TEST_METHOD(SizeConstructor)
		{
			const auto width = 1;
			const auto height = 2;
			SIZE size{ width, height };
			Point point{ size };
			Assert.AreEqual(width, point.x);
			Assert.AreEqual(height, point.y);
		}

		TEST_METHOD(PackConstructor)
		{
			const auto left = 1;
			const auto top = 2;
			Point point{ MAKEWPARAM(left, top) };
			Assert.AreEqual(left, point.x);
			Assert.AreEqual(top, point.y);
		}

		TEST_METHOD(PackConstructor2)
		{
			const auto left = 1;
			const auto top = 2;
			Point point{ MAKELPARAM(left, top) };
			Assert.AreEqual(left, point.x);
			Assert.AreEqual(top, point.y);
		}

		TEST_METHOD(GetCursorPos_Valid)
		{
			const auto left = 1;
			const auto top = 2;
			UnitTest::ApiMock<
				decltype(&::GetCursorPos),
				&::GetCursorPos>
				mock([](POINT* value)
				{
					Assert.IsNotNull(value);
					value->x = left;
					value->y = top;
					return TRUE;
				});
			auto result = Point::GetCursor();
			Assert.AreEqual(left, result.x);
			Assert.AreEqual(top, result.y);
		}

		TEST_METHOD(GetCursorPos_Exception)
		{
			UnitTest::ApiMock<
				decltype(&::GetCursorPos),
				&::GetCursorPos>
				mock([](POINT*)
				{
					return FALSE;
				});
			try
			{
				Point::GetCursor();
				Assert.Fail();
			}
			catch (const Exception& exception)
			{
				Assert.AreEqual(std::string{ "GetCursorPos" }, exception.GetLocation());
			}
		}

		TEST_METHOD(Set)
		{
			const auto left = 1;
			const auto top = 2;
			Point point;
			point.Set(left, top);
			Assert.AreEqual(left, point.x);
			Assert.AreEqual(top, point.y);
		}

		TEST_METHOD(Pack)
		{
			const auto left = 1;
			const auto top = 2;
			Point point{ left, top };
			auto result = point.Pack();
			Assert.AreEqual(left, LOWORD(result));
			Assert.AreEqual(top, HIWORD(result));
		}

		TEST_METHOD(GetLeft)
		{
			const auto left = 1;
			Point point{ left, 0 };
			auto result = point.GetLeft();
			Assert.AreEqual(left, result);
		}

		TEST_METHOD(GetTop)
		{
			const auto top = 1;
			Point point{ 0, top };
			auto result = point.GetTop();
			Assert.AreEqual(top, result);
		}

		TEST_METHOD(SetLeft)
		{
			const auto left = 1;
			Point point;
			point.SetLeft(left);
			Assert.AreEqual(left, point.x);
		}

		TEST_METHOD(SetTop)
		{
			const auto top = 1;
			Point point;
			point.SetTop(top);
			Assert.AreEqual(top, point.y);
		}

		TEST_METHOD(PlusSize)
		{
			const auto left = 1;
			const auto top = 2;
			const auto width = 3;
			const auto height = 4;
			Point point{ left, top };
			auto result = point + Size{ width, height };
			Assert.AreEqual(left + width, result.x);
			Assert.AreEqual(top + height, result.y);
		}

		TEST_METHOD(PlusEqualsSize)
		{
			const auto left = 1;
			const auto top = 2;
			const auto width = 3;
			const auto height = 4;
			Point point{ left, top };
			auto& result = point += Size{ width, height };
			Assert.AreEqual(&point, &result);
			Assert.AreEqual(left + width, result.x);
			Assert.AreEqual(top + height, result.y);
		}

		TEST_METHOD(MinusPoint)
		{
			const auto left1 = 1;
			const auto top1 = 2;
			const auto left2 = 3;
			const auto top2 = 4;
			auto result = Point{ left1, top1 } - Point{ left2, top2 };
			Assert.AreEqual(left1 - left2, result.cx);
			Assert.AreEqual(top1 - top2, result.cy);
		}

		TEST_METHOD(EqualTo_DifferentLeft)
		{
			Assert.IsFalse(Point{ 1, 2 } == Point{ 3, 2 });
		}

		TEST_METHOD(EqualTo_DifferentTop)
		{
			Assert.IsFalse(Point{ 1, 2 } == Point{ 1, 3 });
		}

		TEST_METHOD(EqualTo_Equal)
		{
			Assert.IsTrue(Point{ 1, 2 } == Point{ 1, 2 });
		}

		TEST_METHOD(NotEqualTo_DifferentLeft)
		{
			Assert.IsTrue(Point{ 1, 2 } != Point{ 3, 2 });
		}

		TEST_METHOD(NotEqualTo_DifferentTop)
		{
			Assert.IsTrue(Point{ 1, 2 } != Point{ 1, 3 });
		}

		TEST_METHOD(NotEqualTo_Equal)
		{
			Assert.IsFalse(Point{ 1, 2 } != Point{ 1, 2 });
		}
	};
}

