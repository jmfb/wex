#pragma once
#include "Size.h"

namespace Wex
{
	class Point : public POINT
	{
	public:
		Point();
		Point(int left, int top);
		Point(const POINT& point);
		Point(const SIZE& size);
		Point(unsigned long pack);
		Point(const Point& rhs) = default;
		~Point() = default;

		Point& operator=(const Point& rhs) = default;

		static const Point UseDefault;
		static const Point TopLeft;
		static Point GetCursor();

		void Set(int left, int top);
		unsigned long Pack() const;

		int GetLeft() const;
		int GetTop() const;
		void SetLeft(int value);
		void SetTop(int value);

		Point operator+(const SIZE& size) const;
		Point& operator+=(const SIZE& size);
		Size operator-(const POINT& value) const;

		bool operator==(const POINT& value) const;
		bool operator!=(const POINT& value) const;

	private:
		friend class PointTest;
	};
}

