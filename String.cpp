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

	bool String::IgnoreCaseTraits::eq(char c1, char c2)
	{
		return EqualIgnoreCase()(c1, c2);
	}

	bool String::IgnoreCaseTraits::lt(char c1, char c2)
	{
		return LessIgnoreCase()(c1, c2);
	}

	int String::IgnoreCaseTraits::compare(const char* s1, const char* s2, std::size_t n)
	{
		while (n--)
		{
			if (LessIgnoreCase()(*s1, *s2))
				return -1;
			if (LessIgnoreCase()(*s2, *s1))
				return 1;
			++s1;
			++s2;
		}
		return 0;
	}

	const char* String::IgnoreCaseTraits::find(const char* s, int n, char a)
	{
		while (n--)
		{
			if (EqualIgnoreCase()(*s, a))
				return s;
			++s;
		}
		return nullptr;
	}
}

std::string operator"" _s(const char* value, std::size_t length)
{
	return { value, length };
}

Wex::String::IgnoreCaseString operator"" _ics(const char* value, std::size_t length)
{
	return { value, length };
}

bool operator==(const std::string& s1, const Wex::String::IgnoreCaseString& s2)
{
	return Wex::String::AreEqual(s1, s2);
}

bool operator!=(const std::string& s1, const Wex::String::IgnoreCaseString& s2)
{
	return !Wex::String::AreEqual(s1, s2);
}

bool operator==(const char* s1, const Wex::String::IgnoreCaseString& s2)
{
	return Wex::String::AreEqual(s1, s2);
}

bool operator!=(const char* s1, const Wex::String::IgnoreCaseString& s2)
{
	return !Wex::String::AreEqual(s1, s2);
}

bool operator==(const Wex::String::IgnoreCaseString& s1, const std::string& s2)
{
	return Wex::String::AreEqual(s1, s2);
}

bool operator!=(const Wex::String::IgnoreCaseString& s1, const std::string& s2)
{
	return !Wex::String::AreEqual(s1, s2);
}

bool operator==(const Wex::String::IgnoreCaseString& s1, const char* s2)
{
	return Wex::String::AreEqual(s1, s2);
}

bool operator!=(const Wex::String::IgnoreCaseString& s1, const char* s2)
{
	return !Wex::String::AreEqual(s1, s2);
}

