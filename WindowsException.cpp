#include "WindowsInclude.h"
#include "WindowsException.h"
#include "LocalMemory.h"

namespace Wex
{
	std::string WindowsException::FormatMessage(int code)
	{
		LocalMemory<char> buffer;
		auto formatOptions =
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS;
		auto result = ::FormatMessage(
			formatOptions,
			nullptr,
			code,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			reinterpret_cast<char*>(&buffer),
			0,
			nullptr);
		if (result)
			return buffer.Get();
		return {};
	}
}

