#pragma once
#include "Exception.h"
#include <string>

namespace Wex
{
	class WindowsException
	{
	public:
		static std::string FormatMessage(int code);
	};
}

#define ThrowWindowsError(errorCode, location) \
	{ \
		int intErrorCode = errorCode; \
		auto description = Wex::WindowsException::FormatMessage(intErrorCode); \
		ThrowException(location, intErrorCode, description); \
	}

#define CheckWindowsError(isError, errorCode, location) \
	if (isError) \
		ThrowWindowError(errorCode, location);

#define CheckLastWindowsError(isError, location) \
	if (isError) \
		ThrowWindowsError(::GetLastError(), location);

