#include "WindowsInclude.h"
#include "Time.h"
#include <cstring>

namespace Wex
{
	FILETIME Time::ConvertFileTimeUtcToLocalFileTime(const FILETIME& fileTimeUtc)
	{
		FILETIME fileTimeLocal;
		std::memset(&fileTimeLocal, 0, sizeof(fileTimeLocal));
		::FileTimeToLocalFileTime(&fileTimeUtc, &fileTimeLocal);
		return fileTimeLocal;
	}
	
	SYSTEMTIME Time::ConvertFileTimeToSystemTime(const FILETIME& fileTime)
	{
		SYSTEMTIME systemTime;
		std::memset(&systemTime, 0, sizeof(systemTime));
		::FileTimeToSystemTime(&fileTime, &systemTime);
		return systemTime;
	}
	
	std::tm Time::ConvertSystemTimeToTm(const SYSTEMTIME& systemTime)
	{
		std::tm tm;
		tm.tm_sec = systemTime.wSecond;
		tm.tm_min = systemTime.wMinute;
		tm.tm_hour = systemTime.wHour;
		tm.tm_mday = systemTime.wDay;
		tm.tm_mon = systemTime.wMonth - 1;
		tm.tm_year = systemTime.wYear - 1900;
		return tm;
	}
	
	std::time_t Time::ConvertTmToTimeT(std::tm tm)
	{
		return std::mktime(&tm);
	}
	
	std::chrono::system_clock::time_point Time::ConvertTimeTToTimePoint(std::time_t timeT)
	{
		return std::chrono::system_clock::from_time_t(timeT);
	}
	
	std::chrono::system_clock::time_point Time::ConvertFileTimeUtcToTimePoint(const FILETIME& fileTimeUtc)
	{
		return ConvertTimeTToTimePoint(
			ConvertTmToTimeT(
			ConvertSystemTimeToTm(
			ConvertFileTimeToSystemTime(
			ConvertFileTimeUtcToLocalFileTime(
				fileTimeUtc)))));
	}
}

