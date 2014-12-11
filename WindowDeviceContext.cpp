#include "WindowsInclude.h"
#include "WindowDeviceContext.h"
#include "WindowsException.h"

namespace Wex
{
	WindowDeviceContext::WindowDeviceContext(HWND window)
		: window(window)
	{
		dc = ::GetWindowDC(window);
		CheckLastWindowsError(dc == nullptr, "GetWindowDC");
	}

	WindowDeviceContext::~WindowDeviceContext()
	{
		::ReleaseDC(window, dc);
	}
}

