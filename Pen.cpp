#include "WindowsInclude.h"
#include "Pen.h"
#include "WindowsException.h"

namespace Wex
{
	Pen::Pen(int style, int width, COLORREF color)
	{
		Create(style, width, color);
	}
	
	void Pen::Create(int style, int width, COLORREF color)
	{
		auto result = ::CreatePen(style, width, color);
		CheckLastWindowsError(result == nullptr, "CreatePen");
		Attach(result);
	}
}

