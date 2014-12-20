#pragma once
#include <chrono>
#include <ctime>

namespace Wex
{
	class Time
	{
	public:
		static FILETIME ConvertFileTimeUtcToLocalFileTime(const FILETIME& fileTimeUtc);
		static SYSTEMTIME ConvertFileTimeToSystemTime(const FILETIME& fileTime);
		static std::tm ConvertSystemTimeToTm(const SYSTEMTIME& systemTime);
		static std::time_t ConvertTmToTimeT(std::tm tm);
		static std::chrono::system_clock::time_point ConvertTimeTToTimePoint(std::time_t timeT);
		static std::chrono::system_clock::time_point ConvertFileTimeUtcToTimePoint(const FILETIME& fileTimeUtc);

	private:
		friend class TimeTest;
	};
}

