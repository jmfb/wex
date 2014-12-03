#include "WindowsInclude.h"
#include "Rect.h"
#include "Exception.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(RectTest)
	{
	public:
		RectTest()
		{
		}

		TEST_METHOD(UseDefaultValue)
		{
			Assert.AreEqual(CW_USEDEFAULT, Rect::UseDefault.left);
			Assert.AreEqual(CW_USEDEFAULT, Rect::UseDefault.top);
			Assert.AreEqual(CW_USEDEFAULT, Rect::UseDefault.GetWidth());
			Assert.AreEqual(CW_USEDEFAULT, Rect::UseDefault.GetHeight());
		}

		TEST_METHOD(EmptyValue)
		{
			Assert.AreEqual(0, Rect::Empty.left);
			Assert.AreEqual(0, Rect::Empty.top);
			Assert.AreEqual(0, Rect::Empty.right);
			Assert.AreEqual(0, Rect::Empty.bottom);
		}

		TEST_METHOD(DefaultConstructor)
		{
			Rect rect;
			Assert.AreEqual(0, rect.left);
			Assert.AreEqual(0, rect.top);
			Assert.AreEqual(0, rect.right);
			Assert.AreEqual(0, rect.bottom);
		}

		TEST_METHOD(MemberwiseConstructor)
		{
			const auto left = 1;
			const auto top = 2;
			const auto right = 3;
			const auto bottom = 4;
			Rect rect{ left, top, right, bottom };
			Assert.AreEqual(left, rect.left);
			Assert.AreEqual(top, rect.top);
			Assert.AreEqual(right, rect.right);
			Assert.AreEqual(bottom, rect.bottom);
		}

		TEST_METHOD(RectConstructor)
		{
			const auto left = 1;
			const auto top = 2;
			const auto right = 3;
			const auto bottom = 4;
			RECT value{ left, top, right, bottom };
			Rect rect{ value };
			Assert.AreEqual(left, rect.left);
			Assert.AreEqual(top, rect.top);
			Assert.AreEqual(right, rect.right);
			Assert.AreEqual(bottom, rect.bottom);
		}

		TEST_METHOD(PointSizeConstructor)
		{
			const auto left = 1;
			const auto top = 2;
			const auto right = 3;
			const auto bottom = 4;
			Point topLeft{ left, top };
			Size size{ right - left, bottom - top };
			Rect rect{ topLeft, size };
			Assert.AreEqual(left, rect.left);
			Assert.AreEqual(top, rect.top);
			Assert.AreEqual(right, rect.right);
			Assert.AreEqual(bottom, rect.bottom);
		}

		TEST_METHOD(PointPointConstructor)
		{
			const auto left = 1;
			const auto top = 2;
			const auto right = 3;
			const auto bottom = 4;
			Point topLeft{ left, top };
			Point bottomRight{ right, bottom };
			Rect rect{ topLeft, bottomRight };
			Assert.AreEqual(left, rect.left);
			Assert.AreEqual(top, rect.top);
			Assert.AreEqual(right, rect.right);
			Assert.AreEqual(bottom, rect.bottom);
		}

		TEST_METHOD(Set_Valid)
		{
			const auto left = 1;
			const auto top = 2;
			const auto right = 3;
			const auto bottom = 4;
			Rect rect;
			API_MOCK(::SetRect) mock([&](RECT* rc, int l, int t, int r, int b)
			{
				Assert.AreEqual(&rect, rc);
				Assert.AreEqual(left, l);
				Assert.AreEqual(top, t);
				Assert.AreEqual(right, r);
				Assert.AreEqual(bottom, b);
				return TRUE;
			});
			rect.Set(left, top, right, bottom);
		}

		TEST_METHOD(Set_Exception)
		{
			API_MOCK(::SetRect) mock([](RECT*, int, int, int, int)
			{
				return FALSE;
			});
			Assert.ThrowsType<Exception>(
				[]{ Rect{}.Set(0, 0, 0, 0); },
				[](const Exception& exception)
				{
					Assert.AreEqual(std::string{ "SetRect" }, exception.GetLocation());
				});
		}

		TEST_METHOD(SetEmpty_Valid)
		{
			Rect rect{ 1, 1, 1, 1 };
			API_MOCK(::SetRectEmpty) mock([&](RECT* rc)
			{
				Assert.AreEqual(&rect, rc);
				return TRUE;
			});
			rect.SetEmpty();
		}

		TEST_METHOD(SetEmpty_Exception)
		{
			API_MOCK(::SetRectEmpty) mock([](RECT*)
			{
				return FALSE;
			});
			Assert.ThrowsType<Exception>(
				[]{ Rect{ 0, 0, 0, 0 }.SetEmpty(); },
				[](const Exception& exception)
				{
					Assert.AreEqual(std::string{ "SetRectEmpty" }, exception.GetLocation());
				});
		}

		TEST_METHOD(Copy_Valid)
		{
			Rect rect;
			Rect value;
			UnitTest::ApiMock<
				decltype(&::CopyRect),
				&::CopyRect>
				mock([&](RECT* dest, const RECT* src)
				{
					Assert.AreEqual(&rect, dest);
					Assert.AreEqual(&value, src);
					return TRUE;
				});
			rect.Copy(value);
		}

		TEST_METHOD(Copy_Exception)
		{
			API_MOCK(::CopyRect) mock([](RECT*, const RECT*)
			{
				return FALSE;
			});
			Assert.ThrowsType<Exception>(
				[]{ Rect{}.Copy({}); },
				[](const Exception& exception)
				{
					Assert.AreEqual(std::string{ "CopyRect" }, exception.GetLocation());
				});
		}

		TEST_METHOD(GetWidth)
		{
			const auto left = 1;
			const auto width = 2;
			Rect rect{ Point{ left, 0 }, Size{ width, 0 } };
			auto result = rect.GetWidth();
			Assert.AreEqual(width, result);
		}

		TEST_METHOD(GetHeight)
		{
			const auto top = 1;
			const auto height = 2;
			Rect rect{ Point{ 0, top }, Size{ 0, height } };
			auto result = rect.GetHeight();
			Assert.AreEqual(height, result);
		}

		TEST_METHOD(SetWidth)
		{
			const auto width = 10;
			Rect rect{ Point{ 1, 2 }, Size{ 0, 0 } };
			rect.SetWidth(width);
			Assert.AreEqual(width, rect.GetWidth());
		}

		TEST_METHOD(SetHeight)
		{
			const auto height = 10;
			Rect rect{ Point{ 1, 2 }, Size{ 0, 0 } };
			rect.SetHeight(height);
			Assert.AreEqual(height, rect.GetHeight());
		}

		TEST_METHOD(GetTopLeft)
		{
			const auto left = 1;
			const auto top = 2;
			Rect rect{ left, top, 0, 0 };
			auto result = rect.GetTopLeft();
			Assert.AreEqual(left, result.x);
			Assert.AreEqual(top, result.y);
		}

		TEST_METHOD(GetBottomRight)
		{
			const auto right = 1;
			const auto bottom = 2;
			Rect rect{ 0, 0, right, bottom };
			auto result = rect.GetBottomRight();
			Assert.AreEqual(right, result.x);
			Assert.AreEqual(bottom, result.y);
		}

		TEST_METHOD(GetCenter_IntegerDivision)
		{
			Rect rect{ Point{ 1, 2 }, Size{ 7, 9 } };
			auto result = rect.GetCenter();
			Assert.AreEqual(4, result.x);
			Assert.AreEqual(6, result.y);
		}

		TEST_METHOD(GetCenter_Valid)
		{
			Rect rect{ Point{ 1, 2 }, Size{ 6, 8 } };
			auto result = rect.GetCenter();
			Assert.AreEqual(4, result.x);
			Assert.AreEqual(6, result.y);
		}

		TEST_METHOD(GetSize)
		{
			const auto width = 1;
			const auto height = 2;
			Rect rect{ Point{}, Size{ width, height } };
			auto result = rect.GetSize();
			Assert.AreEqual(width, result.cx);
			Assert.AreEqual(height, result.cy);
		}

		TEST_METHOD(Offset_Valid)
		{
			const auto horizontal = 1;
			const auto vertical = 2;
			Rect rect;
			API_MOCK(::OffsetRect) mock([&](RECT* rc, int dx, int dy)
			{
				Assert.AreEqual(&rect, rc);
				Assert.AreEqual(horizontal, dx);
				Assert.AreEqual(vertical, dy);
				return TRUE;
			});
			auto& result = rect.Offset({ horizontal, vertical });
			Assert.AreSame(rect, result);
		}

		TEST_METHOD(Offset_Exception)
		{
			API_MOCK(::OffsetRect) mock([](RECT*,int,int)
			{
				return FALSE;
			});
			Assert.ThrowsType<Exception>(
				[]{ Rect{}.Offset({}); },
				[](const Exception& exception)
				{
					Assert.AreEqual(std::string{ "OffsetRect" }, exception.GetLocation());
				});
		}

		TEST_METHOD(MoveTo)
		{
			const auto left = 7;
			const auto top = 10;
			const auto width = 2;
			const auto height = 3;
			Rect rect{ Point{ 1, 2 }, Size{ width, height } };
			auto& result = rect.MoveTo({ left, top });
			Assert.AreSame(rect, result);
			Assert.AreEqual(left, rect.left);
			Assert.AreEqual(top, rect.top);
			Assert.AreEqual(left + width, rect.right);
			Assert.AreEqual(top + height, rect.bottom);
		}

		TEST_METHOD(Inflate_Valid)
		{
			const auto horizontal = 1;
			const auto vertical = 2;
			Rect rect;
			API_MOCK(::InflateRect) mock([&](RECT* rc, int dx, int dy)
			{
				Assert.AreEqual(&rect, rc);
				Assert.AreEqual(horizontal, dx);
				Assert.AreEqual(vertical, dy);
				return TRUE;
			});
			auto& result = rect.Inflate({ horizontal, vertical });
			Assert.AreSame(rect, result);
		}

		TEST_METHOD(Inflate_Exception)
		{
			API_MOCK(::InflateRect) mock([](RECT*,int,int)
			{
				return FALSE;
			});
			Assert.ThrowsType<Exception>(
				[]{ Rect{}.Inflate({}); },
				[](const Exception& exception)
				{
					Assert.AreEqual(std::string{ "InflateRect" }, exception.GetLocation());
				});
		}

		TEST_METHOD(Adjust_True)
		{
			const auto windowStyle = 1ul;
			const auto windowExStyle = 2ul;
			const auto hasMenu = true;
			Rect rect;
			API_MOCK(::AdjustWindowRectEx) mock([&](RECT* rc, DWORD style, BOOL menu, DWORD exstyle)
			{
				Assert.AreEqual(&rect, rc);
				Assert.AreEqual(windowStyle, style);
				Assert.AreEqual(hasMenu ? TRUE : FALSE, menu);
				Assert.AreEqual(windowExStyle, exstyle);
				return TRUE;
			});
			auto& result = rect.Adjust(windowStyle, windowExStyle, hasMenu);
			Assert.AreSame(rect, result);
		}

		TEST_METHOD(Adjust_Exception)
		{
			API_MOCK(::AdjustWindowRectEx) mock([](RECT*,DWORD,BOOL,DWORD)
			{
				return FALSE;
			});
			Assert.ThrowsType<Exception>(
				[]{ Rect{}.Adjust(0); },
				[](const Exception& exception)
				{
					Assert.AreEqual(std::string{ "AdjustWindowRectEx" }, exception.GetLocation());
				});
		}

		TEST_METHOD(Contains_True)
		{
			const auto left = 1;
			const auto top = 2;
			Rect rect;
			API_MOCK(::PtInRect) mock([&](const RECT* rc, POINT pt)
			{
				Assert.AreEqual(&rect, rc);
				Assert.AreEqual(left, pt.x);
				Assert.AreEqual(top, pt.y);
				return TRUE;
			});
			Assert.IsTrue(rect.Contains({ left, top }));
		}

		TEST_METHOD(Contains_False)
		{
			API_MOCK(::PtInRect) mock([](const RECT*,POINT)
			{
				return FALSE;
			});
			Assert.IsFalse(Rect{}.Contains({}));
		}

		TEST_METHOD(IsEmpty_True)
		{
			Rect rect;
			API_MOCK(::IsRectEmpty) mock([&](const RECT* rc)
			{
				Assert.AreEqual(&rect, rc);
				return TRUE;
			});
			Assert.IsTrue(rect.IsEmpty());
		}

		TEST_METHOD(IsEmpty_False)
		{
			API_MOCK(::IsRectEmpty) mock([](const RECT*)
			{
				return FALSE;
			});
			Assert.IsFalse(Rect{}.IsEmpty());
		}

		TEST_METHOD(Intersect)
		{
			const auto left = 1;
			const auto top = 2;
			const auto right = 3;
			const auto bottom = 4;
			Rect rect;
			Rect value;
			API_MOCK(::IntersectRect) mock([&](RECT* dest, const RECT* rc1, const RECT* rc2)
			{
				Assert.IsNotNull(dest);
				*dest = { left, top, right, bottom };
				Assert.AreEqual(&rect, rc1);
				Assert.AreEqual(&value, rc2);
				return TRUE;
			});
			auto result = rect & value;
			Assert.AreEqual(left, result.left);
			Assert.AreEqual(top, result.top);
			Assert.AreEqual(right, result.right);
			Assert.AreEqual(bottom, result.bottom);
		}

		TEST_METHOD(IntersectEquals)
		{
			Rect rect{ 0, 0, 100, 100 };
			Rect value{ 50, 50, 200, 200 };
			auto& result = rect &= value;
			Assert.AreSame(rect, result);
			Assert.AreEqual(50, rect.left);
			Assert.AreEqual(50, rect.top);
			Assert.AreEqual(100, rect.right);
			Assert.AreEqual(100, rect.bottom);
		}

		TEST_METHOD(Union)
		{
			const auto left = 1;
			const auto top = 2;
			const auto right = 3;
			const auto bottom = 4;
			Rect rect;
			Rect value;
			API_MOCK(::UnionRect) mock([&](RECT* dest, const RECT* rc1, const RECT* rc2)
			{
				Assert.IsNotNull(dest);
				*dest = { left, top, right, bottom };
				Assert.AreEqual(&rect, rc1);
				Assert.AreEqual(&value, rc2);
				return TRUE;
			});
			auto result = rect | value;
			Assert.AreEqual(left, result.left);
			Assert.AreEqual(top, result.top);
			Assert.AreEqual(right, result.right);
			Assert.AreEqual(bottom, result.bottom);
		}

		TEST_METHOD(UnionEquals)
		{
			Rect rect{ 0, 0, 100, 100 };
			Rect value{ 50, 50, 200, 200 };
			auto& result = rect |= value;
			Assert.AreSame(rect, result);
			Assert.AreEqual(0, rect.left);
			Assert.AreEqual(0, rect.top);
			Assert.AreEqual(200, rect.right);
			Assert.AreEqual(200, rect.bottom);
		}

		TEST_METHOD(Subtract)
		{
			const auto left = 1;
			const auto top = 2;
			const auto right = 3;
			const auto bottom = 4;
			Rect rect;
			Rect value;
			API_MOCK(::SubtractRect) mock([&](RECT* dest, const RECT* rc1, const RECT* rc2)
			{
				Assert.IsNotNull(dest);
				*dest = { left, top, right, bottom };
				Assert.AreEqual(&rect, rc1);
				Assert.AreEqual(&value, rc2);
				return TRUE;
			});
			auto result = rect - value;
			Assert.AreEqual(left, result.left);
			Assert.AreEqual(top, result.top);
			Assert.AreEqual(right, result.right);
			Assert.AreEqual(bottom, result.bottom);
		}

		TEST_METHOD(SubtractEquals)
		{
			Rect rect{ 0, 50, 100, 100 };
			Rect value{ 50, 0, 200, 100 };
			auto& result = rect -= value;
			Assert.AreSame(rect, result);
			Assert.AreEqual(0, rect.left);
			Assert.AreEqual(50, rect.top);
			Assert.AreEqual(50, rect.right);
			Assert.AreEqual(100, rect.bottom);
		}

		TEST_METHOD(EqualTo_True)
		{
			Rect rect;
			Rect value;
			API_MOCK(::EqualRect) mock([&](const RECT* rc1, const RECT* rc2)
			{
				Assert.AreEqual(&rect, rc1);
				Assert.AreEqual(&value, rc2);
				return TRUE;
			});
			Assert.IsTrue(rect == value);
		}

		TEST_METHOD(EqualTo_False)
		{
			API_MOCK(::EqualRect) mock([](const RECT*,const RECT*)
			{
				return FALSE;
			});
			Assert.IsFalse(Rect{} == Rect{});
		}

		TEST_METHOD(NotEqualTo_True)
		{
			Rect rect;
			Rect value;
			API_MOCK(::EqualRect) mock([&](const RECT* rc1, const RECT* rc2)
			{
				Assert.AreEqual(&rect, rc1);
				Assert.AreEqual(&value, rc2);
				return FALSE;
			});
			Assert.IsTrue(rect != value);
		}

		TEST_METHOD(NotEqualTo_False)
		{
			API_MOCK(::EqualRect) mock([](const RECT*,const RECT*)
			{
				return TRUE;
			});
			Assert.IsFalse(Rect{} != Rect{});
		}
	};
}

