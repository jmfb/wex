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

	Size DeviceContext::GetTextSize()
	{
		AssertValid();
		TEXTMETRIC metrics = {0};
		auto result = ::GetTextMetrics(dc, &metrics);
		CheckLastWindowsError(!result, "GetTextMetrics");
		return { metrics.tmAveCharWidth, metrics.tmHeight };
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

	COLORREF DeviceContext::GetBackColor()
	{
		AssertValid();
		auto result = ::GetBkColor(dc);
		CheckLastWindowsError(result == CLR_INVALID, "GetBkColor");
		return result;
	}

	COLORREF DeviceContext::SetTextColor(COLORREF color)
	{
		AssertValid();
		auto oldColor = ::SetTextColor(dc, color);
		CheckLastWindowsError(oldColor == CLR_INVALID, "SetTextColor");
		return oldColor;
	}

	COLORREF DeviceContext::GetTextColor()
	{
		AssertValid();
		auto result = ::GetTextColor(dc);
		CheckLastWindowsError(result == CLR_INVALID, "GetTextColor");
		return result;
	}

	Point DeviceContext::MoveTo(const POINT& point)
	{
		AssertValid();
		Point previousPosition;
		auto result = ::MoveToEx(dc, point.x, point.y, &previousPosition);
		CheckLastWindowsError(!result, "MoveToEx");
		return previousPosition;
	}

	void DeviceContext::LineTo(const POINT& point)
	{
		AssertValid();
		auto result = ::LineTo(dc, point.x, point.y);
		CheckLastWindowsError(!result, "LineTo");
	}

	Point DeviceContext::DrawLine(const std::vector<POINT>& points)
	{
		CheckError(points.size() < 2, 0, "Line must contain at least 2 points.");
		auto previousPosition = MoveTo(points[0]);
		for (auto index = 1ul; index < points.size(); ++index)
			LineTo(points[index]);
		return previousPosition;
	}

	void DeviceContext::AssertValid() const
	{
		if (dc == nullptr)
			ThrowException("dc", 0, "Null device context.");
	}
}

