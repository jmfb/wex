#pragma once

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

		void FillRect(const RECT& rect, HBRUSH brush);
		void FillSolidRect(const RECT& rect, COLORREF color);

		COLORREF SetBackColor(COLORREF color);

	protected:
		void AssertValid() const;

		HDC dc = nullptr;

	private:
		friend class DeviceContextTest;
	};
}

