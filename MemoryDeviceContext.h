#pragma once
#include "DeviceContext.h"
#include "Bitmap.h"
#include "Rect.h"

namespace Wex
{
	class MemoryDeviceContext : public DeviceContext
	{
	public:
		MemoryDeviceContext(HDC dc, const RECT* rc = nullptr);
		MemoryDeviceContext(const MemoryDeviceContext& rhs) = delete;
		~MemoryDeviceContext();

		MemoryDeviceContext& operator=(const MemoryDeviceContext& rhs) = delete;

	private:
		friend class MemoryDeviceContextTest;
		DeviceContext originalDeviceContext;
		Bitmap bitmap;
		HGDIOBJ oldBitmap = nullptr;
		Rect rect;
	};
}

