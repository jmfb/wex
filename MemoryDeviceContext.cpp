#include "WindowsInclude.h"
#include "MemoryDeviceContext.h"
#include "WindowsException.h"

namespace Wex
{
	MemoryDeviceContext::MemoryDeviceContext(HDC dc, const RECT* rc)
		: originalDeviceContext{ dc }
	{
		if (rc == nullptr)
			::GetClipBox(dc, &rect);
		else
			rect = *rc;

		this->dc = ::CreateCompatibleDC(originalDeviceContext);
		CheckLastWindowsError(dc == nullptr, "CreateCompatibleDC");

		auto devicePixels = rect.GetSize();
		::LPtoDP(dc, reinterpret_cast<POINT*>(&devicePixels), 1);
		bitmap.CreateCompatible(originalDeviceContext, devicePixels);
		oldBitmap = ::SelectObject(this->dc, bitmap);

		::SetWindowOrgEx(this->dc, rect.left, rect.top, nullptr);
	}
	
	MemoryDeviceContext::~MemoryDeviceContext()
	{
		::BitBlt(
			originalDeviceContext,
			rect.left,
			rect.top,
			rect.GetWidth(),
			rect.GetHeight(),
			dc,
			rect.left,
			rect.top,
			SRCCOPY);
		::SelectObject(dc, oldBitmap);
		::DeleteDC(dc);
	}
}

