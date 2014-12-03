#pragma once
#include "Point.h"
#include "Size.h"

namespace Wex
{
	class Rect : public RECT
	{
	public:
		Rect();
		Rect(
			int left,
			int top,
			int right,
			int bottom);
		Rect(const RECT& rect);
		Rect(const POINT& topLeft, const SIZE& size);
		Rect(const POINT& topLeft, const POINT& bottomRight);
		Rect(const Rect& rhs) = default;
		~Rect() = default;

		Rect& operator=(const Rect& rhs) = default;

		static const Rect UseDefault;
		static const Rect Empty;

		void Set(
			int left,
			int top,
			int right,
			int bottom);
		void SetEmpty();
		void Copy(const RECT& value);

		int GetWidth() const;
		int GetHeight() const;
		void SetWidth(int value);
		void SetHeight(int value);

		Point GetTopLeft() const;
		Point GetBottomRight() const;
		Point GetCenter() const;
		Size GetSize() const;

		Rect& Offset(const SIZE& size);
		Rect& MoveTo(const POINT& point);
		Rect& Inflate(const SIZE& size);
		Rect& Adjust(
			unsigned long windowStyle,
			unsigned long windowExStyle = 0,
			bool hasMenu = false);

		bool Contains(const POINT& point) const;
		bool IsEmpty() const;

		Rect operator&(const RECT& value) const;
		Rect& operator&=(const RECT& value);
		Rect operator|(const RECT& value) const;
		Rect& operator|=(const RECT& value);
		Rect operator-(const RECT& value) const;
		Rect& operator-=(const RECT& value);

		bool operator==(const RECT& value) const;
		bool operator!=(const RECT& value) const;

	private:
		friend class RectTest;
	};
}

