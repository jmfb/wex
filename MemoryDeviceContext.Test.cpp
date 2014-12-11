#include "WindowsInclude.h"
#include "MemoryDeviceContext.h"
#include "Exception.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(MemoryDeviceContextTest)
	{
	public:
		MemoryDeviceContextTest()
		{
		}

#if 0
		TEST_METHOD(HandleConstructor_DefaultRectWithDestructor)
		{
			const auto sourceDeviceContext = reinterpret_cast<HDC>(1);
			const auto left = 2;
			const auto top = 3;
			const auto width = 4;
			const auto height = 5;
			const auto dc = reinterpret_cast<HDC>(6);
			const auto deviceWidth = 7;
			const auto deviceHeight = 8;
			const auto bitmap = reinterpret_cast<HBITMAP>(9);
			const auto oldBitmap = reinterpret_cast<HBITMAP>(10);
			API_MOCK(::CreateCompatibleDC) mockCreate([=](HDC h)
			{
				Assert.AreEqual(sourceDeviceContext, h);
				return dc;
			});
			API_MOCK(::GetClipBox) mockClip([=](HDC h, RECT* rc)
			{
				Assert.AreEqual(sourceDeviceContext, h);
				Assert.IsNotNull(rc);
				*rc = Rect{ Point{ left, top }, Size{ width, height } };
				return 0;
			});
			API_MOCK(::LPtoDP) mockConvert([=](HDC h, POINT* p, int c)
			{
				Assert.AreEqual(sourceDeviceContext, h);
				Assert.IsNotNull(p);
				Assert.AreEqual(1, c);
				p->x = deviceWidth;
				p->y = deviceHeight;
				return TRUE;
			});
			API_MOCK(::CreateCompatibleBitmap) mockCreateBitmap(
				[&](HDC h, int cx, int cy)
				{
					Assert.AreEqual(dc, h);
					Assert.AreEqual(deviceWidth, cx);
					Assert.AreEqual(deviceHeight, cy);
					return bitmap;
				});
			API_MOCK(::SelectObject) mockSelect([=](HDC h, HGDIOBJ o) -> HGDIOBJ
			{
				Assert.AreEqual(dc, h);
				if (o == bitmap)
					return oldBitmap;
				Assert.AreEqual(oldBitmap, o);
				return nullptr;
			});
			API_MOCK(::SetWindowOrgEx) mockOrg([=](HDC h, int x, int y, POINT* p)
			{
				Assert.AreEqual(dc, h);
				Assert.AreEqual(left, x);
				Assert.AreEqual(top, y);
				Assert.IsNull(p);
				return TRUE;
			});
			API_MOCK(::BitBlt) mockBit(
				[=](HDC s, int x, int y, int w, int h, HDC d, int dx, int dy, DWORD o)
				{
					Assert.AreEqual(sourceDeviceContext, s);
					Assert.AreEqual(left, x);
					Assert.AreEqual(top, y);
					Assert.AreEqual(width, w);
					Assert.AreEqual(height, h);
					Assert.AreEqual(dc, d);
					Assert.AreEqual(left, dx);
					Assert.AreEqual(top, dy);
					Assert.AreEqual(SRCCOPY, o);
					return TRUE;
				});
			API_MOCK(::DeleteDC) mockDeleteContext([=](HDC h)
			{
				Assert.AreEqual(dc, h);
				return TRUE;
			});
			API_MOCK(::DeleteObject) mockDeleteBitmap([=](HGDIOBJ object)
			{
				Assert.AreEqual(bitmap, object);
				return TRUE;
			});
			MemoryDeviceContext deviceContext{ sourceDeviceContext };
			Assert.AreEqual(dc, deviceContext.dc);
		}

		TEST_METHOD(HandleConstructor_RectWithDestructor)
		{
		}
#endif

		TEST_METHOD(HandleConstructor_Exception)
		{
			API_MOCK(::CreateCompatibleDC) mock([](HDC)
			{
				return static_cast<HDC>(nullptr);
			});
			Assert.ThrowsType<Exception>(
				[]{ MemoryDeviceContext{ nullptr }; },
				[](const Exception& exception)
				{
					Assert.AreEqual(std::string{ "CreateCompatibleDC" }, exception.GetLocation());
				});
		}
	};
}

