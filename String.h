#pragma once
#include <string>
#include <cstring>

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

		template <typename Predicate>
		class IgnoreCase
		{
		public:
			bool operator()(char c1, char c2)
			{
				return Predicate()(
					std::tolower(c1),
					std::tolower(c2));
			}
		};

		using EqualIgnoreCase = IgnoreCase<std::equal_to<char>>;
		using LessIgnoreCase = IgnoreCase<std::less<char>>;

		class IgnoreCaseTraits : public std::char_traits<char>
		{
		public:
			static bool eq(char c1, char c2);
			static bool lt(char c1, char c2);
			static int compare(const char* s1, const char* s2, std::size_t n);
			static const char* find(const char* s, int n, char a);
		};

		using IgnoreCaseString = std::basic_string<char, IgnoreCaseTraits>;

		template <typename Traits1, typename Traits2>
		static bool IsLess(
			const std::basic_string<char, Traits1>& s1,
			const std::basic_string<char, Traits2>& s2)
		{
			return std::lexicographical_compare(
				s1.begin(),
				s1.end(),
				s2.begin(),
				s2.end(),
				LessIgnoreCase());
		}

		template <typename Traits>
		static bool IsLess(
			const char* s1,
			const std::basic_string<char, Traits>& s2)
		{
			return std::lexicographical_compare(
				s1,
				s1 + std::strlen(s1),
				s2.begin(),
				s2.end(),
				LessIgnoreCase());
		}

		template <typename Traits>
		static bool IsLess(
			const std::basic_string<char, Traits>& s1,
			const char* s2)
		{
			return std::lexicographical_compare(
				s1.begin(),
				s1.end(),
				s2,
				s2 + std::strlen(s2),
				LessIgnoreCase());
		}

		template <typename Traits1, typename Traits2>
		static bool AreEqual(
			const std::basic_string<char, Traits1>& s1,
			const std::basic_string<char, Traits2>& s2)
		{
			return s1.size() == s2.size() && std::equal(
				s1.begin(),
				s1.end(),
				s2.begin(),
				EqualIgnoreCase());
		}

		template <typename Traits>
		static bool AreEqual(
			const char* s1,
			const std::basic_string<char, Traits>& s2)
		{
			auto length = std::strlen(s1);
			return length == s2.size() && std::equal(
				s1,
				s1 + length,
				s2.begin(),
				EqualIgnoreCase());
		}

		template <typename Traits>
		static bool AreEqual(
			const std::basic_string<char, Traits>& s1,
			const char* s2)
		{
			auto length = std::strlen(s2);
			return s1.size() == length && std::equal(
				s1.begin(),
				s1.end(),
				s2,
				EqualIgnoreCase());
		}

	private:
		friend class StringTest;
	};
}

std::string operator"" _s(const char* value, std::size_t length);
Wex::String::IgnoreCaseString operator"" _ics(const char* value, std::size_t length);

bool operator==(const std::string& s1, const Wex::String::IgnoreCaseString& s2);
bool operator!=(const std::string& s1, const Wex::String::IgnoreCaseString& s2);
bool operator==(const char* s1, const Wex::String::IgnoreCaseString& s2);
bool operator!=(const char* s1, const Wex::String::IgnoreCaseString& s2);
bool operator==(const Wex::String::IgnoreCaseString& s1, const std::string& s2);
bool operator!=(const Wex::String::IgnoreCaseString& s1, const std::string& s2);
bool operator==(const Wex::String::IgnoreCaseString& s1, const char* s2);
bool operator!=(const Wex::String::IgnoreCaseString& s1, const char* s2);

