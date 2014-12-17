#pragma once
#include "Rect.h"
#include "Size.h"
#include "Point.h"
#include <string>
#include <vector>

namespace Wex
{
	class DeviceContext
	{
	public:
		DeviceContext() = default;
		DeviceContext(HDC dc);
		DeviceContext(const DeviceContext& rhs) = delete;
		~DeviceContext() = default;

		DeviceContext& operator=(const DeviceContext& rhs) = delete;

		operator HDC() const;

		HGDIOBJ Select(HGDIOBJ object);

		void FillRect(const RECT& rect, HBRUSH brush);
		void FillSolidRect(const RECT& rect, COLORREF color);

		Rect MeasureString(const std::string& text, const RECT& rect);
		Size GetTextSize();
		void DrawText(const std::string& text, const RECT& rect);

		COLORREF SetBackColor(COLORREF color);
		COLORREF GetBackColor();
		COLORREF SetTextColor(COLORREF color);
		COLORREF GetTextColor();

		Point MoveTo(const POINT& point);
		void LineTo(const POINT& point);
		Point DrawLine(const std::vector<POINT>& points);

	protected:
		void AssertValid() const;

		HDC dc = nullptr;

	private:
		friend class DeviceContextTest;
	};
}

