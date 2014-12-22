#pragma once
#include <string>
#include <vector>
#include <chrono>
#include "ScopedResource.h"

namespace Wex
{
	class FilePolicy
	{
	public:
		using Resource = HANDLE;
		static constexpr Resource Default = INVALID_HANDLE_VALUE;
		static void Release(Resource resource);
	};

	class File : public ScopedResource<FilePolicy>
	{
	public:
		File() = default;
		using ScopedResource<FilePolicy>::ScopedResource;
		~File() = default;

		static bool Exists(const std::string& fullPath);
		static void Copy(
			const std::string& sourceFileName,
			const std::string& destinationFileName);
		static void CopyOver(
			const std::string& sourceFileName,
			const std::string& destinationFileName);
		static std::chrono::system_clock::time_point GetLastWrite(
			const std::string& fullPath);
		static std::string ReadAllText(const std::string& fullPath);
		static std::vector<std::string> ReadLines(const std::string& fullPath);

	private:
		friend class FileTest;
	};
}

