#include "WindowsInclude.h"
#include "Directory.h"
#include "File.h"
#include "Path.h"
#include "FindFile.h"
#include "WindowsException.h"
#include "Flag.h"

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

	std::vector<FileInfo> Directory::Find(
		const std::string& directory,
		const std::string& filter)
	{
		std::vector<FileInfo> results;
		FindFile find;
		auto fullPath = Path::Combine(directory, filter);
		for (auto found = find.FindFirstFile(fullPath); found; found = find.FindNextFile())
		{
			const auto& fileData = find.GetCurrentFileData();
			std::string fileName{ fileData.cFileName };
			if (fileName == "." || fileName == "..")
				continue;
			auto isDirectory = Flag::Test(
				fileData.dwFileAttributes,
				FILE_ATTRIBUTE_DIRECTORY);
			results.emplace_back(Path::Combine(directory, fileName), isDirectory);
		}
		return results;
	}
}

