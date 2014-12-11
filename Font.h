#pragma once
#include "GraphicsObject.h"
#include <string>
#include <vector>

namespace Wex
{
	class Font : public GraphicsObject<HFONT>
	{
	public:
		enum Attribute
		{
			Italic,
			Underline,
			Strikeout
		};
		
		Font() = default;
		Font(
			const std::string& family,
			int height,
			unsigned long weight = FW_DONTCARE,
			const std::vector<Attribute>& attributes = {});
		using GraphicsObject<HFONT>::GraphicsObject;
		~Font() = default;

		static int CalculateHeight(HDC dc, int point);

		void Create(
			const std::string& family,
			int height,
			unsigned long weight = FW_DONTCARE,
			const std::vector<Attribute>& attributes = {});

	private:
		friend class FontTest;
	};
}

