#include "WindowsInclude.h"
#include "WindowDeviceContext.h"
#include "Exception.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(WindowDeviceContextTest)
	{
	public:
		WindowDeviceContextTest()
		{
		}

		TEST_METHOD(WindowConstructor_ValidWithDestructor)
		{
			const auto window = reinterpret_cast<HWND>(1);
			const auto dc = reinterpret_cast<HDC>(2);
			API_MOCK(::GetWindowDC) mockGet([=](HWND h)
			{
				Assert.AreEqual(window, h);
				return dc;
			});
			API_MOCK(::ReleaseDC) mockRelease([=](HWND h, HDC d)
			{
				Assert.AreEqual(window, h);
				Assert.AreEqual(dc, d);
				return 0;
			});
			WindowDeviceContext deviceContext{ window };
			Assert.AreEqual(window, deviceContext.window);
			Assert.AreEqual(dc, deviceContext.dc);
		}

		TEST_METHOD(WindowConstructor_Exception)
		{
			API_MOCK(::GetWindowDC) mock([](HWND)
			{
				return static_cast<HDC>(nullptr);
			});
			Assert.ThrowsType<Exception>(
				[]{ WindowDeviceContext{ nullptr }; },
				[](const Exception& exception)
				{
					Assert.AreEqual(std::string{ "GetWindowDC" }, exception.GetLocation());
				});
		}
	};
}

