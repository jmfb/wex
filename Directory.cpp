#include "WindowsInclude.h"
#include "Directory.h"
#include "File.h"
#include "WindowsException.h"

namespace Wex
{
	bool Directory::Exists(const std::string& value)
	{
		File file{ ::CreateFile(
			value.c_str(),
			0,
			0,
			nullptr,
			OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS,
			nullptr) };
		return !file.IsNull();
	}
	
	void Directory::Create(const std::string& value)
	{
		if (Exists(value))
			return;
		auto result = ::SHCreateDirectoryEx(
			nullptr,
			value.c_str(),
			nullptr);
		CheckLastWindowsError(result != 0, "SHCreateDirectoryEx");
	}
}

