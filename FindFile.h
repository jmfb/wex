#pragma once
#include "ScopedResource.h"
#include <string>

namespace Wex
{
	class FindFilePolicy
	{
	public:
		using Resource = HANDLE;
		static constexpr Resource Default = INVALID_HANDLE_VALUE;
		static void Release(Resource resource);
	};
	
	class FindFile : public ScopedResource<FindFilePolicy>
	{
	public:
		FindFile() = default;
		using ScopedResource<FindFilePolicy>::ScopedResource;
		~FindFile() = default;

		bool FindFirstFile(const std::string& fullPath);
		bool FindNextFile();

		WIN32_FIND_DATA& GetCurrentFileData();
		const WIN32_FIND_DATA& GetCurrentFileData() const;

	private:
		friend class FindFileTest;
		WIN32_FIND_DATA fileData;
	};
}

