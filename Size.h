#pragma once

namespace Wex
{
	class Size : public SIZE
	{
	public:
		Size();
		Size(int width, int height);
		Size(const SIZE& size);
		Size(const POINT& point);
		Size(unsigned long pack);
		Size(const Size& rhs) = default;
		~Size() = default;

		Size& operator=(const Size& rhs) = default;

		void Set(int width, int height);
		unsigned long Pack() const;

		int GetWidth() const;
		int GetHeight() const;
		void SetWidth(int value);
		void SetHeight(int value);

		Size operator+(const SIZE& value) const;
		Size& operator+=(const SIZE& value);
		Size operator-(const SIZE& value) const;
		Size& operator-=(const SIZE& value);
		Size operator-() const;
		Size operator*(int multiplier) const;
		Size& operator*=(int multiplier);
		Size operator/(int divisor) const;
		Size& operator/=(int divisor);

		bool operator==(const SIZE& value) const;
		bool operator!=(const SIZE& value) const;

	private:
		friend class SizeTest;
	};
}

