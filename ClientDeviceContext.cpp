#include "WindowsInclude.h"
#include "ClientDeviceContext.h"
#include "WindowsException.h"

namespace Wex
{
	ClientDeviceContext::ClientDeviceContext(HWND window)
		: window(window)
	{
		dc = ::GetDC(window);
		CheckLastWindowsError(dc == nullptr, "GetDC");
	}
	
	ClientDeviceContext::~ClientDeviceContext()
	{
		::ReleaseDC(window, dc);
	}
}

