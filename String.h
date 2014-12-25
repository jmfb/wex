#pragma once
#include <string>

namespace Wex
{
	class String
	{
	public:
		static std::string TrimStart(const std::string& value);
		static std::string TrimEnd(const std::string& value);
		static std::string Trim(const std::string& value);

		static std::string PadRight(
			const std::string& value,
			int length,
			char padding = ' ');
		static std::string PadLeft(
			const std::string& value,
			int length,
			char padding = ' ');

		static std::string ToLower(const std::string& value);
		static std::string ToUpper(const std::string& value);
		
	private:
		friend class StringTest;
	};
}

