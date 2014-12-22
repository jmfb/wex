#pragma once
#include <string>
#include <vector>
#include "FileInfo.h"

namespace Wex
{
	class Directory
	{
	public:
		static bool Exists(const std::string& value);
		static void Create(const std::string& value);

		static std::vector<FileInfo> Find(
			const std::string& directory,
			const std::string& filter);

	private:
		friend class DirectoryTest;
	};
}

