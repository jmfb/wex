#include "WindowsInclude.h"
#include "Bitmap.h"
#include "Exception.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(BitmapTest)
	{
	public:
		BitmapTest()
		{
		}

		TEST_METHOD(DefaultConstructor)
		{
			Bitmap bitmap;
		}

		TEST_METHOD(CreateConstructor)
		{
			const SIZE size{ 1, 2 };
			const auto planes = 3;
			const auto bitsPerPixel = 4;
			const auto bits = reinterpret_cast<void*>(5);
			CLASS_MOCK(Bitmap::Create) mock(
				[&](Bitmap*,
					const SIZE& s,
					int p,
					int bpp,
					const void* b)
				{
					Assert.AreSame(size, s);
					Assert.AreEqual(planes, p);
					Assert.AreEqual(bitsPerPixel, bpp);
					Assert.AreEqual(bits, b);
				});
			Bitmap bitmap{ size, planes, bitsPerPixel, bits };
		}

		TEST_METHOD(CompatibleConstructor)
		{
			const auto dc = reinterpret_cast<HDC>(1);
			const SIZE size{ 2, 3 };
			CLASS_MOCK(Bitmap::CreateCompatible) mock(
				[&](Bitmap*, HDC h, const SIZE& s)
				{
					Assert.AreEqual(dc, h);
					Assert.AreSame(size, s);
				});
			Bitmap bitmap{ dc, size };
		}

		TEST_METHOD(Create_Valid)
		{
			const auto width = 1;
			const auto height = 2;
			const auto planes = 3;
			const auto bitsPerPixel = 4;
			const auto bits = reinterpret_cast<void*>(5);
			const auto handle = reinterpret_cast<HBITMAP>(6);
			API_MOCK(::CreateBitmap) mock(
				[&](int cx, int cy, int p, int bpp, const void* b)
				{
					Assert.AreEqual(width, cx);
					Assert.AreEqual(height, cy);
					Assert.AreEqual(planes, p);
					Assert.AreEqual(bitsPerPixel, bpp);
					Assert.AreEqual(bits, b);
					return handle;
				});
			Bitmap bitmap;
			bitmap.Create({ width, height }, planes, bitsPerPixel, bits);
			Assert.AreEqual(handle, bitmap.Detach());
		}

		TEST_METHOD(Create_Exception)
		{
			API_MOCK(::CreateBitmap) mock([](int,int,int,int,const void*)
			{
				return static_cast<HBITMAP>(nullptr);
			});
			Assert.ThrowsType<Exception>(
				[]{ Bitmap{}.Create({ 0, 0 }, 0, 0, nullptr); },
				[](const Exception& exception)
				{
					Assert.AreEqual(std::string{ "CreateBitmap" }, exception.GetLocation());
				});
		}

		TEST_METHOD(CreateCompatible_Valid)
		{
			const auto dc = reinterpret_cast<HDC>(1);
			const auto width = 2;
			const auto height = 3;
			const auto handle = reinterpret_cast<HBITMAP>(4);
			API_MOCK(::CreateCompatibleBitmap) mock(
				[&](HDC h, int cx, int cy)
				{
					Assert.AreEqual(dc, h);
					Assert.AreEqual(width, cx);
					Assert.AreEqual(height, cy);
					return handle;
				});
			Bitmap bitmap;
			bitmap.CreateCompatible(dc, { width, height });
			Assert.AreEqual(handle, bitmap.Detach());
		}

		TEST_METHOD(CreateCompatible_Exception)
		{
			API_MOCK(::CreateCompatibleBitmap) mock([](HDC,int,int)
			{
				return static_cast<HBITMAP>(nullptr);
			});
			Assert.ThrowsType<Exception>(
				[]{ Bitmap{}.CreateCompatible(nullptr, { 0, 0 }); },
				[](const Exception& exception)
				{
					Assert.AreEqual(std::string{ "CreateCompatibleBitmap" }, exception.GetLocation());
				});
		}
	};
}

