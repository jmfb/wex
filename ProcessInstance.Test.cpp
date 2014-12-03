#include "WindowsInclude.h"
#include "ProcessInstance.h"
#include "Exception.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(ProcessInstanceTest)
	{
	public:
		ProcessInstanceTest()
		{
		}

		TEST_METHOD(Initialize_Success)
		{
			UnitTest::ApiMock<
				decltype(&::InitCommonControlsEx),
				&::InitCommonControlsEx> mockInit(
				[](const INITCOMMONCONTROLSEX* data)
				{
					Assert.IsNotNull(data);
					Assert.AreEqual(sizeof(INITCOMMONCONTROLSEX), data->dwSize);
					Assert.AreNotEqual(0ul, data->dwICC);
					return TRUE;
				});
			ProcessInstance::Initialize(nullptr);
		}

		TEST_METHOD(Initialize_Exception)
		{
			UnitTest::ApiMock<
				decltype(&::InitCommonControlsEx),
				&::InitCommonControlsEx> mockInit(
				[](const INITCOMMONCONTROLSEX* data)
				{
					return FALSE;
				});
			try
			{
				ProcessInstance::Initialize(nullptr);
				Assert.Fail();
			}
			catch (const Exception& exception)
			{
				Assert.AreEqual(std::string{ "InitCommonControlsEx" }, exception.GetLocation());
			}
		}

		TEST_METHOD(Get)
		{
			const auto handle = reinterpret_cast<HINSTANCE>(1);
			ProcessInstance::Initialize(handle);
			auto result = ProcessInstance::Get();
			Assert.AreEqual(handle, result);
		}
	};
}

