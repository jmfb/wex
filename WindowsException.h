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

#define CheckLastWindowsError(isError, location) \
	if (isError) \
	{ \
		int errorCode = ::GetLastError(); \
		auto description = Wex::WindowsException::FormatMessage(errorCode); \
		ThrowException(location, errorCode, description); \
	}

