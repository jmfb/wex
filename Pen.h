#pragma once
#include "GraphicsObject.h"

namespace Wex
{
	class Pen : public GraphicsObject<HPEN>
	{
	public:
		Pen() = default;
		Pen(int style, int width, COLORREF color);
		using GraphicsObject<HPEN>::GraphicsObject;
		~Pen() = default;

		void Create(int style, int width, COLORREF color);

	private:
		friend class PenTest;
	};
}

