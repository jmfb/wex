#include "String.h"
#include <cctype>
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace Wex
{
	std::string String::TrimStart(const std::string& value)
	{
		std::string::size_type index = 0;
		while (index < value.size())
		{
			if (!std::isspace(value[index]))
				break;
			++index;
		}
		return value.substr(index);
	}

	std::string String::TrimEnd(const std::string& value)
	{
		auto index = value.size();
		while (index > 0)
		{
			if (!std::isspace(value[index - 1]))
				break;
			--index;
		}
		return value.substr(0, index);
	}

	std::string String::Trim(const std::string& value)
	{
		return TrimEnd(TrimStart(value));
	}

	std::string String::PadRight(
		const std::string& value,
		int length,
		char padding)
	{
		std::ostringstream out;
		out << std::setw(length) << std::setfill(padding) << std::left << value;
		return out.str();
	}

	std::string String::PadLeft(
		const std::string& value,
		int length,
		char padding)
	{
		std::ostringstream out;
		out << std::setw(length) << std::setfill(padding) << std::right << value;
		return out.str();
	}

	std::string String::ToLower(const std::string& value)
	{
		auto result = value;
		std::transform(
			result.begin(),
			result.end(),
			result.begin(),
			[](char c){ return std::tolower(c); });
		return result;
	}

	std::string String::ToUpper(const std::string& value)
	{
		auto result = value;
		std::transform(
			result.begin(),
			result.end(),
			result.begin(),
			[](char c){ return std::toupper(c); });
		return result;
	}
}

