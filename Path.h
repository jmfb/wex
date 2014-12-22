#pragma once
#include <string>

namespace Wex
{
	class Path
	{
	public:
		static std::string GetModuleFileName(HMODULE module = nullptr);
		static std::string GetFileName(const std::string& fullPath);
		static std::string GetPath(const std::string& fullPath);
		static std::string GetAbsolutePath(const std::string& relativePath);
		static std::string GetLastFolder(const std::string& fullPath);
		static std::string GetTitle(const std::string& fullPath);
		static std::string GetExtension(const std::string& fullPath);
		static std::string Combine(
			const std::string& path1,
			const std::string& path2);

		template <typename... Parts>
		static std::string Combine(
			const std::string& path1,
			const std::string& path2,
			Parts... parts)
		{
			return Combine(Combine(path1, path2), parts...);
		}

	private:
		friend class PathTest;
	};
}

