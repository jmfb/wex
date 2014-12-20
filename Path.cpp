#include "WindowsInclude.h"
#include "Path.h"
#include "WindowsException.h"

namespace Wex
{
	std::string Path::GetModuleFileName(HMODULE module)
	{
		const auto bufferLength = 4096;
		char buffer[bufferLength];
		auto result = ::GetModuleFileName(module, buffer, bufferLength);
		CheckLastWindowsError(result == 0, "GetModuleFileName");
		return buffer;
	}
	
	std::string Path::GetFileName(const std::string& fullPath)
	{
		auto index = fullPath.rfind('\\');
		if (index == std::string::npos)
			return fullPath;
		return fullPath.substr(index + 1);
	}
	
	std::string Path::GetPath(const std::string& fullPath)
	{
		auto index = fullPath.rfind('\\');
		if (index == std::string::npos)
			return "";
		return fullPath.substr(0, index);
	}
	
	std::string Path::GetLastFolder(const std::string& fullPath)
	{
		return GetFileName(GetPath(fullPath));
	}
	
	std::string Path::GetTitle(const std::string& fullPath)
	{
		auto name = GetFileName(fullPath);
		auto index = name.rfind('.');
		if (index == std::string::npos)
			return name;
		return name.substr(0, index);
	}
	
	std::string Path::GetExtension(const std::string& fullPath)
	{
		auto name = GetFileName(fullPath);
		auto index = name.rfind('.');
		if (index == std::string::npos)
			return "";
		return name.substr(index + 1);
	}
	
	std::string Path::Combine(
		const std::string& path1,
		const std::string& path2)
	{
		if (path1.empty())
			return path2;
		if (path2.empty())
			return path1;
		auto trailingSlash = path1.back() == '\\';
		auto leadingSlash = path2[0] == '\\';
		if (!trailingSlash && !leadingSlash)
			return path1 + "\\" + path2;
		if (trailingSlash && leadingSlash)
			return path1 + path2.substr(1);
		return path1 + path2;
	}
}

