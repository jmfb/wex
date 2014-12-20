#include "WindowsInclude.h"
#include "Brush.h"
#include "Exception.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(BrushTest)
	{
	public:
		BrushTest()
		{
		}

		TEST_METHOD(DefaultConstructor)
		{
			Brush brush;
		}

		TEST_METHOD(SolidConstructor)
		{
			const auto color = static_cast<COLORREF>(1);
			CLASS_MOCK(Brush::CreateSolid) mock([&](Brush*, int value)
			{
				Assert.AreEqual(color, value);
			});
			Brush brush{ color };
		}

		TEST_METHOD(PatternConstructor)
		{
			const auto bitmap = reinterpret_cast<HBITMAP>(1);
			CLASS_MOCK(Brush::CreatePattern) mock([&](Brush*, HBITMAP value)
			{
				Assert.AreEqual(bitmap, value);
			});
			Brush brush{ bitmap };
		}

		TEST_METHOD(HatchConstructor)
		{
			const auto style = 1;
			const auto color = static_cast<COLORREF>(2);
			CLASS_MOCK(Brush::CreateHatch) mock([&](Brush*, int s, COLORREF c)
			{
				Assert.AreEqual(style, s);
				Assert.AreEqual(color, c);
			});
			Brush brush{ style, color };
		}

		TEST_METHOD(IndirectConstructor)
		{
			LOGBRUSH logBrush;
			CLASS_MOCK(Brush::CreateIndirect) mock([&](Brush*, const LOGBRUSH& value)
			{
				Assert.AreSame(logBrush, value);
			});
			Brush brush{ logBrush };
		}

		TEST_METHOD(HalftonConstructor)
		{
			CLASS_MOCK(Brush::CreateHalftone) mock([](Brush*){});
			Brush brush{ Brush::Halftone };
		}

		TEST_METHOD(GetSystem)
		{
			const auto colorIndex = 1;
			const auto systemBrush = reinterpret_cast<HBRUSH>(2);
			API_MOCK(::GetSysColorBrush) mock([&](int value)
			{
				Assert.AreEqual(colorIndex, value);
				return systemBrush;
			});
			auto result = Brush::GetSystem(colorIndex);
			Assert.AreEqual(systemBrush, result);
		}

		TEST_METHOD(CreateSolid_Valid)
		{
			const auto color = static_cast<COLORREF>(1);
			const auto handle = reinterpret_cast<HBRUSH>(2);
			API_MOCK(::CreateSolidBrush) mock([&](COLORREF value)
			{
				Assert.AreEqual(color, value);
				return handle;
			});
			Brush brush;
			brush.CreateSolid(color);
			Assert.AreEqual(handle, brush.Detach());
		}

		TEST_METHOD(CreateSolid_Exception)
		{
			API_MOCK(::CreateSolidBrush) mock([](COLORREF)
			{
				return static_cast<HBRUSH>(nullptr);
			});
			Assert.ThrowsType<Exception>(
				[]{ Brush{}.CreateSolid(0); },
				[](const Exception& exception)
				{
					Assert.AreEqual("CreateSolidBrush", exception.GetLocation());
				});
		}

		TEST_METHOD(CreatePattern_Valid)
		{
			const auto bitmap = reinterpret_cast<HBITMAP>(1);
			const auto handle = reinterpret_cast<HBRUSH>(2);
			API_MOCK(::CreatePatternBrush) mock([&](HBITMAP value)
			{
				Assert.AreEqual(bitmap, value);
				return handle;
			});
			Brush brush;
			brush.CreatePattern(bitmap);
			Assert.AreEqual(handle, brush.Detach());
		}

		TEST_METHOD(CreatePattern_Exception)
		{
			API_MOCK(::CreatePatternBrush) mock([](HBITMAP)
			{
				return static_cast<HBRUSH>(nullptr);
			});
			Assert.ThrowsType<Exception>(
				[]{ Brush{}.CreatePattern(nullptr); },
				[](const Exception& exception)
				{
					Assert.AreEqual("CreatePatternBrush", exception.GetLocation());
				});
		}

		TEST_METHOD(CreateHalftone)
		{
			Brush brush;
			brush.CreateHalftone();
			Assert.IsTrue(brush);
		}
	};
}

