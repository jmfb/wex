#pragma once

namespace Wex
{
	template <typename SizeType>
	class IndexIterator
	{
	public:
		IndexIterator(SizeType index)
			: index(index)
		{
		}
		IndexIterator<SizeType>& operator++()
		{
			++index;
			return *this;
		}
		SizeType operator*() const
		{
			return index;
		}
		bool operator==(const IndexIterator<SizeType>& rhs) const
		{
			return index == rhs.index;
		}
		bool operator!=(const IndexIterator<SizeType>& rhs) const
		{
			return index != rhs.index;
		}
	private:
		SizeType index;
	};
}

