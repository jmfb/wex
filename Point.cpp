#include "WindowsInclude.h"
#include "Point.h"
#include "WindowsException.h"

namespace Wex
{
	const Point Point::UseDefault{ CW_USEDEFAULT, CW_USEDEFAULT };
	const Point Point::TopLeft{ };

	Point::Point()
	{
		x = 0;
		y = 0;
	}

	Point::Point(int left, int top)
	{
		x = left;
		y = top;
	}

	Point::Point(const POINT& point)
	{
		x = point.x;
		y = point.y;
	}

	Point::Point(const SIZE& size)
	{
		x = size.cx;
		y = size.cy;
	}

	Point::Point(WPARAM pack)
	{
		x = LOWORD(pack);
		y = HIWORD(pack);
	}

	Point::Point(LPARAM pack)
	{
		x = LOWORD(pack);
		y = HIWORD(pack);
	}

	Point Point::GetCursor()
	{
		Point point;
		auto result = ::GetCursorPos(&point);
		CheckLastWindowsError(!result, "GetCursorPos");
		return point;
	}

	void Point::Set(int left, int top)
	{
		x = left;
		y = top;
	}

	WPARAM Point::Pack() const
	{
		return MAKEWPARAM(x, y);
	}

	int Point::GetLeft() const
	{
		return x;
	}

	int Point::GetTop() const
	{
		return y;
	}

	void Point::SetLeft(int value)
	{
		x = value;
	}

	void Point::SetTop(int value)
	{
		y = value;
	}

	Point Point::operator+(const SIZE& size) const
	{
		return { x + size.cx, y + size.cy };
	}

	Point& Point::operator+=(const SIZE& size)
	{
		x += size.cx;
		y += size.cy;
		return *this;
	}

	Size Point::operator-(const POINT& value) const
	{
		return { x - value.x, y - value.y };
	}

	bool Point::operator==(const POINT& value) const
	{
		return x == value.x && y == value.y;
	}

	bool Point::operator!=(const POINT& value) const
	{
		return x != value.x || y != value.y;
	}
}

