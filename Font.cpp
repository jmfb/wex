#include "WindowsInclude.h"
#include "Font.h"
#include "Range.h"
#include "WindowsException.h"

namespace Wex
{
	Font::Font(
		const std::string& family,
		int height,
		unsigned long weight,
		const std::vector<Attribute>& attributes)
	{
		Create(family, height, weight, attributes);
	}
	
	int Font::CalculateHeight(HDC dc, int point)
	{
		return -::MulDiv(point, ::GetDeviceCaps(dc, LOGPIXELSY), 72);
	}
	
	void Font::Create(
		const std::string& family,
		int height,
		unsigned long weight,
		const std::vector<Attribute>& attributes)
	{
		auto result = ::CreateFont(
			height,
			0,
			0,
			0,
			weight,
			Range::Contains(attributes, Italic) ? TRUE : FALSE,
			Range::Contains(attributes, Underline) ? TRUE : FALSE,
			Range::Contains(attributes, Strikeout) ? TRUE : FALSE,
			ANSI_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			family.c_str());
		CheckLastWindowsError(result == nullptr, "CreateFont");
		Attach(result);
	}
}

