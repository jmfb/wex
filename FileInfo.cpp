#include "WindowsInclude.h"
#include "FileInfo.h"
#include "Path.h"

namespace Wex
{
	FileInfo::FileInfo(
		const std::string& fullPath,
		bool isDirectory)
		: fullPath{ fullPath }, isDirectory{ isDirectory }
	{
	}

	const std::string& FileInfo::GetFullPath() const
	{
		return fullPath;
	}
	
	std::string FileInfo::GetPath() const
	{
		return Path::GetPath(fullPath);
	}
	
	std::string FileInfo::GetFileName() const
	{
		return Path::GetFileName(fullPath);
	}
	
	std::string FileInfo::GetTitle() const
	{
		return Path::GetTitle(fullPath);
	}
	
	std::string FileInfo::GetExtension() const
	{
		return Path::GetExtension(fullPath);
	}
	
	bool FileInfo::IsFile() const
	{
		return !isDirectory;
	}
	
	bool FileInfo::IsDirectory() const
	{
		return isDirectory;
	}
}

