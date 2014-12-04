#pragma once
#include "GraphicsObject.h"

namespace Wex
{
	class Brush : public GraphicsObject<HBRUSH>
	{
	public:
		Brush() = default;
		Brush(COLORREF color);
		Brush(HBITMAP bitmap);
		Brush(int style, COLORREF color);
		Brush(const LOGBRUSH& brush);
		enum HalftoneBrush { Halftone };
		Brush(HalftoneBrush);
		using GraphicsObject<HBRUSH>::GraphicsObject;
		~Brush() = default;

		static HBRUSH GetSystem(int colorIndex);

		void CreateSolid(COLORREF color);
		void CreatePattern(HBITMAP bitmap);
		void CreateHatch(int style, COLORREF color);
		void CreateIndirect(const LOGBRUSH& brush);
		void CreateHalftone();

	private:
		friend class BrushTest;
	};
}

