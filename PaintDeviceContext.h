#pragma once
#include "DeviceContext.h"

namespace Wex
{
	class PaintDeviceContext : public DeviceContext
	{
	public:
		PaintDeviceContext(HWND window);
		PaintDeviceContext(const PaintDeviceContext& rhs) = delete;
		~PaintDeviceContext();

		PaintDeviceContext& operator=(const PaintDeviceContext& rhs) = delete;

	private:
		friend class PaintDeviceContextTest;
		HWND window = nullptr;
		PAINTSTRUCT paintStruct;
	};
}

