#pragma once
#include "Rect.h"
#include <string>

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
		void DrawText(const std::string& text, const RECT& rect);

		COLORREF SetBackColor(COLORREF color);
		COLORREF SetTextColor(COLORREF color);

	protected:
		void AssertValid() const;

		HDC dc = nullptr;

	private:
		friend class DeviceContextTest;
	};
}

