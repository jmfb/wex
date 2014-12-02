#include "Exception.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(ExceptionTest)
	{
	public:
		ExceptionTest()
		{
		}

		TEST_METHOD(MemberwiseConstructor)
		{
			const std::string file{ "file" };
			const int line = 1;
			const std::string whenCompiled{ "whenCompiled" };
			const std::string whenModified{ "whenModified" };
			const std::string function{ "function" };
			const std::string location{ "location" };
			const int errorCode = 2;
			const std::string description{ "description" };
			Exception exception
			{
				file,
				line,
				whenCompiled,
				whenModified,
				function,
				location,
				errorCode,
				description
			};
			Assert.AreEqual(file, exception.GetFile());
			Assert.AreEqual(line, exception.GetLine());
			Assert.AreEqual(whenCompiled, exception.GetWhenCompiled());
			Assert.AreEqual(whenModified, exception.GetWhenModified());
			Assert.AreEqual(function, exception.GetFunction());
			Assert.AreEqual(location, exception.GetLocation());
			Assert.AreEqual(errorCode, exception.GetErrorCode());
			Assert.AreEqual(description, exception.GetDescription());
		}
	
		TEST_METHOD(What)
		{
			Exception exception;
			Assert.AreEqual(
				exception.GetFullDescription().c_str(),
				exception.what());
		}
	
		TEST_METHOD(FullDescription)
		{
			Exception exception
			{
				"file",
				1,
				"whenCompiled",
				"whenModified",
				"function",
				"location",
				2,
				"description"
			};
			std::string expected
			{
				"File:          file\n"
				"Line:          1\n"
				"When Compiled: whenCompiled\n"
				"When Modified: whenModified\n"
				"Function:      function\n"
				"Location:      location\n"
				"Error Code:    2\n"
				"Description:   description\n"
			};
			Assert.AreEqual(expected, exception.GetFullDescription());
		}
	
		TEST_METHOD(ThrowExceptionMacro)
		{
			const std::string location{ "location" };
			const int errorCode = 1;
			const std::string description{ "description" };
			int previousLine = 0;
			try
			{
				previousLine = __LINE__;
				ThrowException(location, errorCode, description);
			}
			catch (const Exception& exception)
			{
				Assert.AreEqual(std::string{ __FILE__ }, exception.GetFile());
				Assert.AreEqual(previousLine + 1, exception.GetLine());
				Assert.AreEqual(std::string{ __DATE__ " " __TIME__ }, exception.GetWhenCompiled());
				Assert.AreEqual(std::string{ __TIMESTAMP__ }, exception.GetWhenModified());
				Assert.AreEqual(std::string{ __FUNCTION__ }, exception.GetFunction());
				Assert.AreEqual(location, exception.GetLocation());
				Assert.AreEqual(errorCode, exception.GetErrorCode());
				Assert.AreEqual(description, exception.GetDescription());
				return;
			}
			Assert.Fail("Should have thrown an exception.");
		}
	};
}

