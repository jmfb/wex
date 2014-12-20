#include "WindowsInclude.h"
#include "File.h"
#include "Time.h"
#include "WindowsException.h"
#include <cstring>

namespace Wex
{
	void FilePolicy::Release(Resource resource)
	{
		::CloseHandle(resource);
	}

	bool File::Exists(const std::string& fullPath)
	{
		File file{ ::CreateFile(
			fullPath.c_str(),
			0,
			0,
			nullptr,
			OPEN_EXISTING,
			0,
			nullptr) };
		return !file.IsNull();
	}

	std::chrono::system_clock::time_point File::GetLastWrite(
		const std::string& fullPath)
	{
		WIN32_FILE_ATTRIBUTE_DATA data;
		std::memset(&data, 0, sizeof(data));
		auto result = ::GetFileAttributesEx(
			fullPath.c_str(),
			GetFileExInfoStandard,
			&data);
		CheckLastWindowsError(result == 0, "GetFileAttributesEx");
		return Time::ConvertFileTimeUtcToTimePoint(
			data.ftLastWriteTime);
	}
}

