#include "WindowsInclude.h"
#include "DeviceContext.h"
#include "WindowsException.h"

namespace Wex
{
	DeviceContext::DeviceContext(HDC dc)
		: dc(dc)
	{
	}

	DeviceContext::operator HDC() const
	{
		return dc;
	}

	HGDIOBJ DeviceContext::Select(HGDIOBJ object)
	{
		AssertValid();
		return ::SelectObject(dc, object);
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

	Rect DeviceContext::MeasureString(const std::string& text, const RECT& rect)
	{
		AssertValid();
		auto boundingRect = rect;
		::DrawText(
			dc,
			text.c_str(),
			text.size(),
			&boundingRect,
			DT_SINGLELINE|DT_NOPREFIX|DT_LEFT|DT_TOP|DT_CALCRECT);
		return boundingRect;
	}

	void DeviceContext::DrawText(const std::string& text, const RECT& rect)
	{
		AssertValid();
		auto boundingRect = rect;
		::DrawText(
			dc,
			text.c_str(),
			text.size(),
			&boundingRect,
			DT_SINGLELINE|DT_NOPREFIX|DT_LEFT|DT_TOP);
	}

	COLORREF DeviceContext::SetBackColor(COLORREF color)
	{
		AssertValid();
		auto oldColor = ::SetBkColor(dc, color);
		CheckLastWindowsError(oldColor == CLR_INVALID, "SetBkColor");
		return oldColor;
	}

	COLORREF DeviceContext::SetTextColor(COLORREF color)
	{
		AssertValid();
		auto oldColor = ::SetTextColor(dc, color);
		CheckLastWindowsError(oldColor == CLR_INVALID, "SetTextColor");
		return oldColor;
	}

	void DeviceContext::AssertValid() const
	{
		if (dc == nullptr)
			ThrowException("dc", 0, "Null device context.");
	}
}

