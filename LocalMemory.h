#pragma once
#include "ScopedResource.h"

namespace Wex
{
	template <typename Value>
	class LocalMemoryPolicy
	{
	public:
		using Resource = Value*;
		static constexpr Resource Default = nullptr;
		static void Release(Resource resource)
		{
			::LocalFree(resource);
		}
	};

	template <typename Value>
	using LocalMemory = ScopedResource<LocalMemoryPolicy<Value>>;
}

