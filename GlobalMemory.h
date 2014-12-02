#pragma once
#include "ScopedResource.h"

namespace Wex
{
	template <typename Value>
	class GlobalMemoryPolicy
	{
	public:
		using Resource = Value*;
		static constexpr Resource Default = nullptr;
		static void Release(Resource resource)
		{
			::GlobalFree(resource);
		}
	};

	template <typename Value>
	using GlobalMemory = ScopedResource<GlobalMemoryPolicy<Value>>;
}

