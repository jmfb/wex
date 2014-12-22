#pragma once
#include <string>

namespace Wex
{
	class FileInfo
	{
	public:
		FileInfo() = default;
		FileInfo(
			const std::string& fullPath,
			bool isDirectory);
		FileInfo(const FileInfo& rhs) = default;
		~FileInfo() = default;

		FileInfo& operator=(const FileInfo& rhs) = default;

		const std::string& GetFullPath() const;
		std::string GetPath() const;
		std::string GetFileName() const;
		std::string GetTitle() const;
		std::string GetExtension() const;
		bool IsFile() const;
		bool IsDirectory() const;

	private:
		friend class FileInfoTest;
		std::string fullPath;
		bool isDirectory = false;
	};
}

