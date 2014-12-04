#include "WindowsInclude.h"
#include "GraphicsObject.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(GraphicsObjectTest)
	{
	public:
		GraphicsObjectTest()
		{
		}

		TEST_METHOD(Release)
		{
			const auto value = reinterpret_cast<HGDIOBJ>(1);
			API_MOCK(::DeleteObject) mock([&](HGDIOBJ object)
			{
				Assert.AreEqual(value, object);
				return TRUE;
			});
			GraphicsObjectPolicy::Release(value);
		}

		TEST_METHOD(ConstructFromGenericObject)
		{
			const auto value = reinterpret_cast<HGDIOBJ>(1);
			GraphicsObject<HBRUSH> handle{ value };
			Assert.AreEqual(value, handle.Get());
		}

		TEST_METHOD(ConstructFromSpecificObject)
		{
			const auto value = reinterpret_cast<HBRUSH>(1);
			GraphicsObject<HBRUSH> handle{ value };
			Assert.AreEqual(value, handle.Get());
		}

		TEST_METHOD(CastToGenericObject)
		{
			GraphicsObject<HBRUSH> handle;
			HGDIOBJ result{ handle };
			Assert.IsNull(result);
		}

		TEST_METHOD(CastToSpecificObject)
		{
			GraphicsObject<HBRUSH> handle;
			HBRUSH result{ handle };
			Assert.IsNull(result);
		}
	};
}

