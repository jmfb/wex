#include "WindowsInclude.h"
#include "ClientDeviceContext.h"
#include "Exception.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(ClientDeviceContextTest)
	{
	public:
		ClientDeviceContextTest()
		{
		}

		TEST_METHOD(WindowConstructor_ValidWithDestructor)
		{
			const auto window = reinterpret_cast<HWND>(1);
			const auto dc = reinterpret_cast<HDC>(2);
			API_MOCK(::GetDC) mockGet([=](HWND h)
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
			ClientDeviceContext deviceContext{ window };
			Assert.AreEqual(window, deviceContext.window);
			Assert.AreEqual(dc, deviceContext.dc);
		}

		TEST_METHOD(WindowConstructor_Exception)
		{
			API_MOCK(::GetDC) mock([](HWND)
			{
				return static_cast<HDC>(nullptr);
			});
			Assert.ThrowsType<Exception>(
				[]{ ClientDeviceContext{ nullptr }; },
				[](const Exception& exception)
				{
					Assert.AreEqual("GetDC", exception.GetLocation());
				});
		}
	};
}

