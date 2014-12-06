#include "WindowsInclude.h"
#include "DeviceContext.h"
#include "WindowsException.h"

namespace Wex
{
	DeviceContext::DeviceContext(HDC dc)
		: dc(dc)
	{
	}
	
	void DeviceContext::FillRect(const RECT& rect, HBRUSH brush)
	{
		AssertValid();
		auto result = ::FillRect(dc, &rect, brush);
		CheckLastWindowsError(!result, "FillRect");
	}
	
	void DeviceContext::FillSolidRect(const RECT& rect, COLORREF color)
	{
		AssertValid();
		auto oldColor = SetBackColor(color);
		auto result = ::ExtTextOut(
			dc,
			0,
			0,
			ETO_OPAQUE,
			&rect,
			nullptr,
			0,
			nullptr);
		CheckLastWindowsError(!result, "ExtTextOut");
		SetBackColor(oldColor);
	}

	COLORREF DeviceContext::SetBackColor(COLORREF color)
	{
		AssertValid();
		auto oldColor = ::SetBkColor(dc, color);
		CheckLastWindowsError(oldColor == CLR_INVALID, "SetBkColor");
		return oldColor;
	}
	
	void DeviceContext::AssertValid() const
	{
		if (dc == nullptr)
			ThrowException("dc", 0, "Null device context.");
	}
}

