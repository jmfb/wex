#pragma once
#include "DeviceContext.h"

namespace Wex
{
	class WindowDeviceContext : public DeviceContext
	{
	public:
		WindowDeviceContext(HWND window);
		WindowDeviceContext(const WindowDeviceContext& rhs) = delete;
		~WindowDeviceContext();

		WindowDeviceContext& operator=(const WindowDeviceContext& rhs) = delete;

	private:
		friend class WindowDeviceContextTest;
		HWND window = nullptr;
	};
}

