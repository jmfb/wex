#include "WindowsInclude.h"
#include "LocalMemory.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(LocalMemoryTest)
	{
	public:
		LocalMemoryTest()
		{
		}

		TEST_METHOD(DefaultValue)
		{
			Assert.IsNull(LocalMemoryPolicy<void>::Default);
		}

		TEST_METHOD(Release)
		{
			void* value = reinterpret_cast<void*>(0x1234);
			UnitTest::ApiMock<
				decltype(&::LocalFree),
				&::LocalFree>
				mock([&](void* actual)
				{
					Assert.AreEqual(value, actual);
					return nullptr;
				});
			LocalMemoryPolicy<void>::Release(value);
		}
	};
}

