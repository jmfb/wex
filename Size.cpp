#include "WindowsInclude.h"
#include "Size.h"
#include "Exception.h"

namespace Wex
{
	Size::Size()
	{
		cx = 0;
		cy = 0;
	}

	Size::Size(int width, int height)
	{
		cx = width;
		cy = height;
	}

	Size::Size(const SIZE& size)
	{
		cx = size.cx;
		cy = size.cy;
	}

	Size::Size(const POINT& point)
	{
		cx = point.x;
		cy = point.y;
	}

	Size::Size(unsigned long pack)
	{
		cx = LOWORD(pack);
		cy = HIWORD(pack);
	}

	void Size::Set(int width, int height)
	{
		cx = width;
		cy = height;
	}

	unsigned long Size::Pack() const
	{
		return MAKEWPARAM(cx, cy);
	}

	int Size::GetWidth() const
	{
		return cx;
	}

	int Size::GetHeight() const
	{
		return cy;
	}

	void Size::SetWidth(int value)
	{
		cx = value;
	}

	void Size::SetHeight(int value)
	{
		cy = value;
	}

	Size Size::operator+(const SIZE& value) const
	{
		return { cx + value.cx, cy + value.cy };
	}

	Size& Size::operator+=(const SIZE& value)
	{
		cx += value.cx;
		cy += value.cy;
		return *this;
	}

	Size Size::operator-(const SIZE& value) const
	{
		return { cx - value.cx, cy - value.cy };
	}

	Size& Size::operator-=(const SIZE& value)
	{
		cx -= value.cx;
		cy -= value.cy;
		return *this;
	}

	Size Size::operator-() const
	{
		return { -cx, -cy };
	}

	Size Size::operator*(int multiplier) const
	{
		return { cx * multiplier, cy * multiplier };
	}

	Size& Size::operator*=(int multiplier)
	{
		cx *= multiplier;
		cy *= multiplier;
		return *this;
	}

	Size Size::operator/(int divisor) const
	{
		if (divisor == 0)
			ThrowException("divisor", 0, "Divide by zero.");
		return { cx / divisor, cy / divisor };
	}

	Size& Size::operator/=(int divisor)
	{
		return *this = *this / divisor;
	}

	bool Size::operator==(const SIZE& value) const
	{
		return cx == value.cx && cy == value.cy;
	}

	bool Size::operator!=(const SIZE& value) const
	{
		return cx != value.cx || cy != value.cy;
	}
}

