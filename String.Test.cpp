#include "String.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(StringTest)
	{
	public:
		StringTest()
		{
		}

		TEST_METHOD(TrimStart_Empty)
		{
			Assert.IsEmpty(String::TrimStart(""));
		}

		TEST_METHOD(TrimStart_LeadingSpace)
		{
			const std::string value{ "value  " };
			Assert.AreEqual(value, String::TrimStart("  " + value));
		}

		TEST_METHOD(TrimStart_NoLeadingSpace)
		{
			const std::string value{ "value  " };
			Assert.AreEqual(value, String::TrimStart(value));
		}

		TEST_METHOD(TrimStart_AllSpaces)
		{
			Assert.IsEmpty(String::TrimStart("  "));
		}

		TEST_METHOD(TrimEnd_Empty)
		{
			Assert.IsEmpty(String::TrimEnd(""));
		}

		TEST_METHOD(TrimEnd_TrailingSpaces)
		{
			const std::string value{ "  value" };
			Assert.AreEqual(value, String::TrimEnd(value + "  "));
		}

		TEST_METHOD(TrimEnd_NoTrailingSpaces)
		{
			const std::string value{ "  value" };
			Assert.AreEqual(value, String::TrimEnd(value));
		}

		TEST_METHOD(TrimEnd_AllSpaces)
		{
			Assert.IsEmpty(String::TrimEnd("  "));
		}

		TEST_METHOD(Trim_Empty)
		{
			Assert.IsEmpty(String::Trim(""));
		}

		TEST_METHOD(Trim_LeadingAndTrailingSpaces)
		{
			const std::string value{ "value" };
			Assert.AreEqual(value, String::Trim("  " + value + "  "));
		}

		TEST_METHOD(Trim_AllSpaces)
		{
			Assert.IsEmpty(String::Trim("  "));
		}

		TEST_METHOD(PadRight_TooLong)
		{
			const std::string value{ "value" };
			Assert.AreEqual(value, String::PadRight(value, value.size(), ' '));
		}

		TEST_METHOD(PadRight_Valid)
		{
			Assert.AreEqual("valueXX", String::PadRight("value", 7, 'X'));
		}

		TEST_METHOD(ToUpper)
		{
			Assert.AreEqual("VALUE", String::ToUpper("Value"));
		}

		TEST_METHOD(ToLower)
		{
			Assert.AreEqual("value", String::ToLower("Value"));
		}

		TEST_METHOD(EqualIgnoreCase_True)
		{
			Assert.IsTrue(String::EqualIgnoreCase()('a', 'A'));
		}

		TEST_METHOD(EqualIgnoreCase_False)
		{
			Assert.IsFalse(String::EqualIgnoreCase()('a', 'b'));
		}

		TEST_METHOD(LessIgnoreCase_True)
		{
			Assert.IsTrue(String::LessIgnoreCase()('a', 'B'));
			Assert.IsTrue(String::LessIgnoreCase()('A', 'b'));
		}

		TEST_METHOD(LessIgnoreCase_False)
		{
			Assert.IsFalse(String::LessIgnoreCase()('b', 'A'));
			Assert.IsFalse(String::LessIgnoreCase()('B', 'a'));
		}

		TEST_METHOD(StringLiteral)
		{
			Assert.AreEqual("value", "value"_s);
		}
		
		TEST_METHOD(IgnoreCaseStringLiteral)
		{
			auto value = "value"_ics;
			std::string s{ value.begin(), value.end() };
			Assert.AreEqual("value", s);
		}

		TEST_METHOD(AreEqual_StringStringTrue)
		{
			Assert.IsTrue(String::AreEqual(
				std::string{ "Value" },
				std::string{ "value" }));
		}

		TEST_METHOD(AreEqual_StringStringFalse)
		{
			Assert.IsFalse(String::AreEqual(
				std::string{ "Value" },
				std::string{ "other" }));
		}

		TEST_METHOD(AreEqual_PointerStringTrue)
		{
			Assert.IsTrue(String::AreEqual(
				"Value",
				std::string{ "value" }));
		}

		TEST_METHOD(AreEqual_PointerStringFalse)
		{
			Assert.IsFalse(String::AreEqual(
				"Value",
				std::string{ "other" }));
		}

		TEST_METHOD(AreEqual_StringPointerTrue)
		{
			Assert.IsTrue(String::AreEqual(
				std::string{ "Value" },
				"value"));
		}

		TEST_METHOD(AreEqual_StringPointerFalse)
		{
			Assert.IsFalse(String::AreEqual(
				std::string{ "Value" },
				"other"));
		}

		TEST_METHOD(ComparisonOperator_IgnoreString)
		{
			Assert.IsTrue("Value"_ics == "value"_s);
			Assert.IsFalse("Value"_ics == "other"_s);
			Assert.IsTrue("Value"_ics != "other"_s);
			Assert.IsFalse("Value"_ics != "value"_s);
		}

		TEST_METHOD(ComparisonOperator_IgnorePointer)
		{
			Assert.IsTrue("Value"_ics == "value");
			Assert.IsFalse("Value"_ics == "other");
			Assert.IsTrue("Value"_ics != "other");
			Assert.IsFalse("Value"_ics != "value");
		}

		TEST_METHOD(ComparisonOperator_StringIgnore)
		{
			Assert.IsTrue("Value"_s == "value"_ics);
			Assert.IsFalse("Value"_s == "other"_ics);
			Assert.IsTrue("Value"_s != "other"_ics);
			Assert.IsFalse("Value"_s != "value"_ics);
		}

		TEST_METHOD(ComparisonOperator_PointerIgnore)
		{
			Assert.IsTrue("Value" == "value"_ics);
			Assert.IsFalse("Value" == "other"_ics);
			Assert.IsTrue("Value" != "other"_ics);
			Assert.IsFalse("Value" != "value"_ics);
		}

		TEST_METHOD(Isanity)
		{
			std::string extension = "h";
			std::string titleExtension = "";
			if (titleExtension == "Test"_ics && extension == "cpp"_ics)
				Assert.Fail();
		}

		TEST_METHOD(LessInsanity)
		{
			Assert.IsFalse(""_s == "Test"_ics);
		}
	};
}

