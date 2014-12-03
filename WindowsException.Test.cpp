#include "WindowsInclude.h"
#include "WindowsException.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(WindowsExceptionTest)
	{
	public:
		WindowsExceptionTest()
		{
		}

		TEST_METHOD(FormatMessage_Valid)
		{
			auto result = WindowsException::FormatMessage(ERROR_ACCESS_DENIED);
			Assert.AreEqual(std::string{ "Access is denied.\r\n" }, result);
		}

		TEST_METHOD(FormatMessage_Invalid)
		{
			auto result = WindowsException::FormatMessage(-1);
			Assert.AreEqual(std::string{ "" }, result);
		}

		TEST_METHOD(CheckLastWindowsError_IsNotError)
		{
			CheckLastWindowsError(false, "location");
		}

		TEST_METHOD(CheckLastWindowsError_IsError)
		{
			const std::string location{ "location" };
			const auto errorCode = 1;
			try
			{
				::SetLastError(errorCode);
				CheckLastWindowsError(true, location);
				Assert.Fail();
			}
			catch (const Exception& exception)
			{
				Assert.AreEqual(location, exception.GetLocation());
				Assert.AreEqual(errorCode, exception.GetErrorCode());
			}
		}
	};
}

