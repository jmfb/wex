#pragma once
#include <algorithm>
#include "IndexSequence.h"

namespace Wex
{
	namespace Range
	{
		template <typename Container, typename Value>
		bool Contains(const Container& container, const Value& value)
		{
			auto iter = std::find(container.begin(), container.end(), value);
			return iter != container.end();
		}
	}
}

