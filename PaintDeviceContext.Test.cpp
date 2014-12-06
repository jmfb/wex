#include "WindowsInclude.h"
#include "PaintDeviceContext.h"
#include "Exception.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(PaintDeviceContextTest)
	{
	public:
		PaintDeviceContextTest()
		{
		}

		TEST_METHOD(Constructor_ValidWithDestructor)
		{
			const auto window = reinterpret_cast<HWND>(1);
			const auto dc = reinterpret_cast<HDC>(2);
			PAINTSTRUCT* paintStruct = nullptr;
			API_MOCK(::BeginPaint) mockBegin([&](HWND h, PAINTSTRUCT* ps)
			{
				Assert.AreEqual(window, h);
				Assert.IsNotNull(ps);
				paintStruct = ps;
				return dc;
			});
			API_MOCK(::EndPaint) mockEnd([&](HWND h, const PAINTSTRUCT* ps)
			{
				Assert.AreEqual(window, h);
				Assert.AreEqual(paintStruct, ps);
				return TRUE;
			});
			PaintDeviceContext deviceContext{ window };
			Assert.AreEqual(dc, deviceContext.dc);
		}

		TEST_METHOD(Constructor_Exception)
		{
			API_MOCK(::BeginPaint) mock([](HWND,PAINTSTRUCT*)
			{
				return static_cast<HDC>(nullptr);
			});
			Assert.ThrowsType<Exception>(
				[]{ PaintDeviceContext{ nullptr }; },
				[](const Exception& exception)
				{
					Assert.AreEqual(std::string{ "BeginPaint" }, exception.GetLocation());
				});
		}
	};
}

