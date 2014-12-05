#include "WindowsInclude.h"
#include "Brush.h"
#include "Bitmap.h"
#include "WindowsException.h"
#include <array>

namespace Wex
{
	Brush::Brush(COLORREF color)
	{
		CreateSolid(color);
	}

	Brush::Brush(HBITMAP bitmap)
	{
		CreatePattern(bitmap);
	}

	Brush::Brush(int style, COLORREF color)
	{
		CreateHatch(style, color);
	}

	Brush::Brush(const LOGBRUSH& brush)
	{
		CreateIndirect(brush);
	}

	Brush::Brush(HalftoneBrush)
	{
		CreateHalftone();
	}

	HBRUSH Brush::GetSystem(int colorIndex)
	{
		return ::GetSysColorBrush(colorIndex);
	}

	void Brush::CreateSolid(COLORREF color)
	{
		auto result = ::CreateSolidBrush(color);
		CheckLastWindowsError(!result, "CreateSolidBrush");
		Attach(result);
	}

	void Brush::CreatePattern(HBITMAP bitmap)
	{
		auto result = ::CreatePatternBrush(bitmap);
		CheckLastWindowsError(!result, "CreatePatternBrush");
		Attach(result);
	}

	void Brush::CreateHatch(int style, COLORREF color)
	{
		auto result = ::CreateHatchBrush(style, color);
		CheckLastWindowsError(!result, "CreateHatchBrush");
		Attach(result);
	}

	void Brush::CreateIndirect(const LOGBRUSH& brush)
	{
		auto result = ::CreateBrushIndirect(&brush);
		CheckLastWindowsError(!result, "CreateBrushIndirect");
		Attach(result);
	}

	void Brush::CreateHalftone()
	{
		std::array<WORD, 8> pattern
		{
			0b0101010101010101,
			0b1010101010101010,
			0b0101010101010101,
			0b1010101010101010,
			0b0101010101010101,
			0b1010101010101010,
			0b0101010101010101,
			0b1010101010101010
		};
		CreatePattern(Bitmap{ { pattern.size(), pattern.size() }, 1, 1, pattern.data() });
	}
}

