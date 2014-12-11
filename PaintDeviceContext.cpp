#include "WindowsInclude.h"
#include "PaintDeviceContext.h"
#include "WindowsException.h"

namespace Wex
{
	PaintDeviceContext::PaintDeviceContext(HWND window)
		: window(window)
	{
		dc = ::BeginPaint(window, &paintStruct);
		CheckLastWindowsError(dc == nullptr, "BeginPaint");
	}

	PaintDeviceContext::~PaintDeviceContext()
	{
		::EndPaint(window, &paintStruct);
	}
}

