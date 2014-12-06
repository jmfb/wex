#pragma once
#include "DeviceContext.h"

namespace Wex
{
	class MemoryDeviceContext : public DeviceContext
	{
	public:
		MemoryDeviceContext() = default;
		MemoryDeviceContext(const MemoryDeviceContext& rhs) = delete;
		~MemoryDeviceContext() = default;

		MemoryDeviceContext& operator=(const MemoryDeviceContext& rhs) = delete;

	private:
		friend class MemoryDeviceContextTest;
	};
}

