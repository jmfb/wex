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
			Assert.AreEqual(std::string{ "" }, String::TrimStart(""));
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
			Assert.AreEqual(std::string{ "" }, String::TrimStart("  "));
		}

		TEST_METHOD(TrimEnd_Empty)
		{
			Assert.AreEqual(std::string{ "" }, String::TrimEnd(""));
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
			Assert.AreEqual(std::string{ "" }, String::TrimEnd("  "));
		}

		TEST_METHOD(Trim_Empty)
		{
			Assert.AreEqual(std::string{ "" }, String::Trim(""));
		}

		TEST_METHOD(Trim_LeadingAndTrailingSpaces)
		{
			const std::string value{ "value" };
			Assert.AreEqual(value, String::Trim("  " + value + "  "));
		}

		TEST_METHOD(Trim_AllSpaces)
		{
			Assert.AreEqual(std::string{ "" }, String::Trim("  "));
		}
	};
}

