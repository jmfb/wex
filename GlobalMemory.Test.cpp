#include "WindowsInclude.h"
#include "GlobalMemory.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(GlobalMemoryTest)
	{
	public:
		GlobalMemoryTest()
		{
		}

		TEST_METHOD(DefaultValue)
		{
			Assert.IsNull(GlobalMemoryPolicy<void>::Default);
		}

		TEST_METHOD(Release)
		{
			void* value = reinterpret_cast<void*>(0x1234);
			UnitTest::ApiMock<
				decltype(&::GlobalFree),
				&::GlobalFree>
				mock([&](void* actual)
				{
					Assert.AreEqual(value, actual);
					return nullptr;
				});
			GlobalMemoryPolicy<void>::Release(value);
		}
	};
}

