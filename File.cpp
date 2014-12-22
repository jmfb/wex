#include "WindowsInclude.h"
#include "File.h"
#include "Time.h"
#include "WindowsException.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>

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

	void File::Copy(
		const std::string& sourceFileName,
		const std::string& destinationFileName)
	{
		auto result = ::CopyFile(
			sourceFileName.c_str(),
			destinationFileName.c_str(),
			TRUE);
		CheckLastWindowsError(!result, "CopyFile");
	}

	void File::CopyOver(
		const std::string& sourceFileName,
		const std::string& destinationFileName)
	{
		auto result = ::CopyFile(
			sourceFileName.c_str(),
			destinationFileName.c_str(),
			FALSE);
		CheckLastWindowsError(!result, "CopyFile");
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

	std::string File::ReadAllText(const std::string& fullPath)
	{
		std::ifstream in(fullPath.c_str());
		std::stringstream buffer;
		in >> buffer.rdbuf();
		return buffer.str();
	}
	
	std::vector<std::string> File::ReadLines(const std::string& fullPath)
	{
		std::ifstream in(fullPath.c_str());
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(in, line))
			lines.push_back(line);
		return lines;
	}
}

