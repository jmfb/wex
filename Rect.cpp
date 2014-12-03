#include "WindowsInclude.h"
#include "Rect.h"
#include "WindowsException.h"

namespace Wex
{
	const Rect Rect::UseDefault
	{
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0
	};
	const Rect Rect::Empty{ };

	Rect::Rect()
	{
		SetEmpty();
	}

	Rect::Rect(
		int left,
		int top,
		int right,
		int bottom)
	{
		Set(left, top, right, bottom);
	}

	Rect::Rect(const RECT& rect)
	{
		Copy(rect);
	}

	Rect::Rect(const POINT& topLeft, const SIZE& size)
	{
		Set(
			topLeft.x,
			topLeft.y,
			topLeft.x + size.cx,
			topLeft.y + size.cy);
	}

	Rect::Rect(const POINT& topLeft, const POINT& bottomRight)
	{
		Set(
			topLeft.x,
			topLeft.y,
			bottomRight.x,
			bottomRight.y);
	}

	void Rect::Set(
		int left,
		int top,
		int right,
		int bottom)
	{
		auto result = ::SetRect(this, left, top, right, bottom);
		CheckLastWindowsError(!result, "SetRect");
	}

	void Rect::SetEmpty()
	{
		auto result = ::SetRectEmpty(this);
		CheckLastWindowsError(!result, "SetRectEmpty");
	}

	void Rect::Copy(const RECT& value)
	{
		auto result = ::CopyRect(this, &value);
		CheckLastWindowsError(!result, "CopyRect");
	}

	int Rect::GetWidth() const
	{
		return right - left;
	}

	int Rect::GetHeight() const
	{
		return bottom - top;
	}

	void Rect::SetWidth(int value)
	{
		right = left + value;
	}

	void Rect::SetHeight(int value)
	{
		bottom = top + value;
	}

	Point Rect::GetTopLeft() const
	{
		return { left, top };
	}

	Point Rect::GetBottomRight() const
	{
		return { right, bottom };
	}

	Point Rect::GetCenter() const
	{
		return
		{
			left + GetWidth() / 2,
			top + GetHeight() / 2
		};
	}

	Size Rect::GetSize() const
	{
		return { GetWidth(), GetHeight() };
	}

	Rect& Rect::Offset(const SIZE& size)
	{
		auto result = ::OffsetRect(this, size.cx, size.cy);
		CheckLastWindowsError(!result, "OffsetRect");
		return *this;
	}

	Rect& Rect::MoveTo(const POINT& point)
	{
		return Offset(Point{ point } - GetTopLeft());
	}

	Rect& Rect::Inflate(const SIZE& size)
	{
		auto result = ::InflateRect(this, size.cx, size.cy);
		CheckLastWindowsError(!result, "InflateRect");
		return *this;
	}

	Rect& Rect::Adjust(
		unsigned long windowStyle,
		unsigned long windowExStyle,
		bool hasMenu)
	{
		auto result = ::AdjustWindowRectEx(
			this,
			windowStyle,
			hasMenu ? TRUE : FALSE,
			windowExStyle);
		CheckLastWindowsError(!result, "AdjustWindowRectEx");
		return *this;
	}

	bool Rect::Contains(const POINT& point) const
	{
		return ::PtInRect(this, point) != 0;
	}

	bool Rect::IsEmpty() const
	{
		return ::IsRectEmpty(this) != 0;
	}

	Rect Rect::operator&(const RECT& value) const
	{
		Rect intersection;
		::IntersectRect(&intersection, this, &value);
		return intersection;
	}

	Rect& Rect::operator&=(const RECT& value)
	{
		return *this = *this & value;
	}

	Rect Rect::operator|(const RECT& value) const
	{
		Rect unionRect;
		::UnionRect(&unionRect, this, &value);
		return unionRect;
	}

	Rect& Rect::operator|=(const RECT& value)
	{
		return *this = *this | value;
	}

	Rect Rect::operator-(const RECT& value) const
	{
		Rect difference;
		::SubtractRect(&difference, this, &value);
		return difference;
	}

	Rect& Rect::operator-=(const RECT& value)
	{
		return *this = *this - value;
	}

	bool Rect::operator==(const RECT& value) const
	{
		return ::EqualRect(this, &value) != 0;
	}

	bool Rect::operator!=(const RECT& value) const
	{
		return ::EqualRect(this, &value) == 0;
	}
}

