#pragma once
#include "DeviceContext.h"

namespace Wex
{
	class ClientDeviceContext : public DeviceContext
	{
	public:
		ClientDeviceContext(HWND window);
		ClientDeviceContext(const ClientDeviceContext& rhs) = delete;
		~ClientDeviceContext();

		ClientDeviceContext& operator=(const ClientDeviceContext& rhs) = delete;

	private:
		friend class ClientDeviceContextTest;
		HWND window = nullptr;
	};
}

