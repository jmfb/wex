#pragma once
#include "GraphicsObject.h"

namespace Wex
{
	class Bitmap : public GraphicsObject<HBITMAP>
	{
	public:
		Bitmap() = default;
		Bitmap(
			const SIZE& size,
			int planes,
			int bitsPerPixel,
			const void* bits);
		Bitmap(HDC dc, const SIZE& size);
		using GraphicsObject<HBITMAP>::GraphicsObject;
		~Bitmap() = default;

		void Create(
			const SIZE& size,
			int planes,
			int bitsPerPixel,
			const void* bits);
		void CreateCompatible(HDC dc, const SIZE& size);

	private:
		friend class BitmapTest;
	};
}

