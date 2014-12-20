#pragma once
#include <string>

namespace Wex
{
	class Directory
	{
	public:
		static bool Exists(const std::string& value);
		static void Create(const std::string& value);

	private:
		friend class DirectoryTest;
	};
}

