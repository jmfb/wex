#include "WindowsInclude.h"
#include "Bitmap.h"
#include "WindowsException.h"

namespace Wex
{
	Bitmap::Bitmap(
		const SIZE& size,
		int planes,
		int bitsPerPixel,
		const void* bits)
	{
		Create(size, planes, bitsPerPixel, bits);
	}
	
	Bitmap::Bitmap(HDC dc, const SIZE& size)
	{
		CreateCompatible(dc, size);
	}
	
	void Bitmap::Create(
		const SIZE& size,
		int planes,
		int bitsPerPixel,
		const void* bits)
	{
		auto result = ::CreateBitmap(
			size.cx,
			size.cy,
			planes,
			bitsPerPixel,
			bits);
		CheckLastWindowsError(!result, "CreateBitmap");
		Attach(result);
	}
	
	void Bitmap::CreateCompatible(HDC dc, const SIZE& size)
	{
		auto result = ::CreateCompatibleBitmap(dc, size.cx, size.cy);
		CheckLastWindowsError(!result, "CreateCompatibleBitmap");
		Attach(result);
	}
}

