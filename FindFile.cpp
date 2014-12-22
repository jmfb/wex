#include "WindowsInclude.h"
#include "FindFile.h"
#include "WindowsException.h"

namespace Wex
{
	void FindFilePolicy::Release(Resource resource)
	{
		::FindClose(resource);
	}
	
	bool FindFile::FindFirstFile(const std::string& fullPath)
	{
		Attach(::FindFirstFile(fullPath.c_str(), &fileData));
		if (!IsNull())
			return true;
		auto lastError = ::GetLastError();
		if (lastError == ERROR_FILE_NOT_FOUND ||
			lastError == ERROR_PATH_NOT_FOUND ||
			lastError == ERROR_NO_MORE_FILES)
			return false;
		ThrowWindowsError(lastError, "FindFirstFile");
	}
	
	bool FindFile::FindNextFile()
	{
		return ::FindNextFile(Get(), &fileData) != 0;
	}
	
	WIN32_FIND_DATA& FindFile::GetCurrentFileData()
	{
		return fileData;
	}
	
	const WIN32_FIND_DATA& FindFile::GetCurrentFileData() const
	{
		return fileData;
	}
}

