#include "WindowsInclude.h"
#include "DeviceContext.h"
#include "Exception.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(DeviceContextTest)
	{
	public:
		DeviceContextTest()
		{
		}

		TEST_METHOD(DefaultConstructor)
		{
			DeviceContext deviceContext;
			Assert.IsNull(deviceContext.dc);
		}

		TEST_METHOD(HandleConstructor)
		{
			const auto dc = reinterpret_cast<HDC>(1);
			DeviceContext deviceContext{ dc };
			Assert.AreEqual(dc, deviceContext.dc);
		}

		TEST_METHOD(FillRect_Valid)
		{
			const auto dc = reinterpret_cast<HDC>(1);
			const RECT rect{ 2, 3, 4, 5 };
			const auto brush = reinterpret_cast<HBRUSH>(6);
			CLASS_MOCK(DeviceContext::AssertValid) mockAssert([](const DeviceContext*){});
			API_MOCK(::FillRect) mock([&](HDC h, const RECT* r, HBRUSH b)
			{
				Assert.AreEqual(dc, h);
				Assert.AreEqual(&rect, r);
				Assert.AreEqual(brush, b);
				return TRUE;
			});
			DeviceContext deviceContext{ dc };
			deviceContext.FillRect(rect, brush);
		}

		TEST_METHOD(FillRect_Exception)
		{
			CLASS_MOCK(DeviceContext::AssertValid) mockAssert([](const DeviceContext*){});
			API_MOCK(::FillRect) mock([](HDC, const RECT*, HBRUSH)
			{
				return FALSE;
			});
			Assert.ThrowsType<Exception>(
				[]{ DeviceContext{}.FillRect({ 0, 0, 0, 0 }, nullptr); },
				[](const Exception& exception)
				{
					Assert.AreEqual(std::string{ "FillRect" }, exception.GetLocation());
				});
		}

		TEST_METHOD(FillSolidRect_Valid)
		{
			//TODO:
			//CLASS_MOCK(DeviceContext::AssertValid) mockAssert([](const DeviceContext*){});
		}

		TEST_METHOD(FillSolidRect_Exception)
		{
			//TODO:
			//CLASS_MOCK(DeviceContext::AssertValid) mockAssert([](const DeviceContext*){});
		}

		TEST_METHOD(SetBackColor_Valid)
		{
			const auto color = static_cast<COLORREF>(1);
			const auto oldColor = static_cast<COLORREF>(2);
			const auto dc = reinterpret_cast<HDC>(3);
			CLASS_MOCK(DeviceContext::AssertValid) mockAssert([](const DeviceContext*){});
			API_MOCK(::SetBkColor) mock([&](HDC h, COLORREF c)
			{
				Assert.AreEqual(dc, h);
				Assert.AreEqual(color, c);
				return oldColor;
			});
			DeviceContext deviceContext{ dc };
			auto result = deviceContext.SetBackColor(color);
			Assert.AreEqual(oldColor, result);
		}

		TEST_METHOD(SetBackColor_Exception)
		{
			CLASS_MOCK(DeviceContext::AssertValid) mockAssert([](const DeviceContext*){});
			API_MOCK(::SetBkColor) mock([](HDC,COLORREF)
			{
				return CLR_INVALID;
			});
			Assert.ThrowsType<Exception>(
				[]{ DeviceContext{}.SetBackColor(0); },
				[](const Exception& exception)
				{
					Assert.AreEqual(std::string{ "SetBkColor" }, exception.GetLocation());
				});
		}

		TEST_METHOD(AssertValid_IsValid)
		{
			DeviceContext{ reinterpret_cast<HDC>(1) }.AssertValid();
		}

		TEST_METHOD(AssertValid_Exception)
		{
			Assert.ThrowsType<Exception>(
				[]{ DeviceContext{}.AssertValid(); },
				[](const Exception& exception)
				{
					Assert.AreEqual(std::string{ "dc" }, exception.GetLocation());
					Assert.AreEqual(0, exception.GetErrorCode());
					Assert.AreEqual(std::string{ "Null device context." }, exception.GetDescription());
				});
		}
	};
}

