#pragma once
#include "IndexIterator.h"

namespace Wex
{
	template <typename SizeType>
	class IndexSequence
	{
	public:
		IndexSequence(SizeType count)
			: count(count)
		{
		}
		IndexIterator<SizeType> begin() const
		{
			return { 0 };
		}
		IndexIterator<SizeType> end() const
		{
			return { count };
		}
	private:
		SizeType count;
	};

	template <typename SizeType>
	inline IndexSequence<SizeType> Indexes(SizeType count)
	{
		return { count };
	}
}

template <typename SizeType>
inline Wex::IndexIterator<SizeType> begin(const Wex::IndexSequence<SizeType>& sequence)
{
	return sequence.begin();
}

template <typename SizeType>
inline Wex::IndexIterator<SizeType> end(const Wex::IndexSequence<SizeType>& sequence)
{
	return sequence.end();
}

