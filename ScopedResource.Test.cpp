#include "WindowsInclude.h"
#include "ScopedResource.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;
#include <memory>

namespace Wex
{
	TEST_CLASS(ScopedResourceTest)
	{
	public:
		ScopedResourceTest()
		{
		}

		class TestPolicy
		{
		public:
			using Resource = int;
			static const Resource Default{ 0 };
			static void Release(Resource resource)
			{
				ReleaseIntercept(resource);
			}
			static void __stdcall ReleaseIntercept(Resource resource)
			{
			}
		};

		using TestResource = ScopedResource<TestPolicy>;

		TEST_METHOD(DefaultConstructor)
		{
			TestResource resource;
			Assert.AreEqual(0, resource.resource);
		}

		TEST_METHOD(ResourceConstructor)
		{
			const auto value = 1;
			TestResource resource{ value };
			Assert.AreEqual(value, resource.resource);
		}

		TEST_METHOD(Destructor)
		{
			UnitTest::ClassMock<
				decltype(&TestResource::Release),
				&TestResource::Release>
				mock([](TestResource*){});
			TestResource resource;
		}

		TEST_METHOD(ValueAssignment)
		{
			const auto value = 1;
			UnitTest::ClassMock<
				decltype(&TestResource::Attach),
				&TestResource::Attach>
				mock([&](TestResource*, int actual)
				{
					Assert.AreEqual(value, actual);
				});
			TestResource resource;
			auto& result = resource = value;
			Assert.AreEqual(std::addressof(result), std::addressof(resource));
		}

		TEST_METHOD(Get)
		{
			const auto value = 1;
			TestResource resource{ value };
			Assert.AreEqual(value, resource.Get());
		}

		TEST_METHOD(Detach)
		{
			const auto value = 1;
			TestResource resource{ value };
			auto result = resource.Detach();
			Assert.AreEqual(0, resource.resource);
			Assert.AreEqual(value, result);
		}

		TEST_METHOD(AttachCurrentValue)
		{
			UnitTest::ClassMock<
				decltype(&TestResource::Release),
				&TestResource::Release>
				mock([](TestResource*){});
			const auto value = 1;
			TestResource resource{ value };
			resource.Attach(value);
			Assert.AreEqual(value, resource.resource);
		}

		TEST_METHOD(AttachNewValue)
		{
			UnitTest::ClassMock<
				decltype(&TestResource::Release),
				&TestResource::Release>
				mock([](TestResource*){});
			mock.Expects(2);
			const auto value = 1;
			TestResource resource;
			resource.Attach(value);
			Assert.AreEqual(value, resource.resource);
		}

		TEST_METHOD(ReleaseDefault)
		{
			UnitTest::ApiMock<
				decltype(&TestPolicy::ReleaseIntercept),
				&TestPolicy::ReleaseIntercept>
				mock([](int){});
			mock.Expects(0);
			TestResource resource;
			resource.Release();
		}

		TEST_METHOD(ReleaseValid)
		{
			const auto value = 1;
			UnitTest::ApiMock<
				decltype(&TestPolicy::ReleaseIntercept),
				&TestPolicy::ReleaseIntercept>
				mock([&](int actual)
				{
					Assert.AreEqual(value, actual);
				});
			TestResource resource{ value };
			resource.Release();
			Assert.AreEqual(0, resource.resource);
		}

		TEST_METHOD(IsNull_True)
		{
			TestResource resource;
			Assert.IsTrue(resource.IsNull());
		}

		TEST_METHOD(IsNull_False)
		{
			TestResource resource{ 1 };
			Assert.IsFalse(resource.IsNull());
		}

		TEST_METHOD(Truthy)
		{
			TestResource resource{ 1 };
			Assert.IsTrue(resource);
		}

		TEST_METHOD(TruthyInIf)
		{
			TestResource resource{ 1 };
			if (resource)
				;
			else
				Assert.Fail();
		}

		TEST_METHOD(Falsy)
		{
			TestResource resource;
			Assert.IsFalse(resource);
		}

		TEST_METHOD(FalseInIf)
		{
			TestResource resource;
			if (!resource)
				;
			else
				Assert.Fail();
		}

		TEST_METHOD(AutomaticCast)
		{
			const auto value = 1;
			TestResource resource{ value };
			int result = resource;
			Assert.AreEqual(value, result);
		}

		TEST_METHOD(AddressOf)
		{
			TestResource resource;
			auto result = &resource;
			Assert.AreEqual(&resource.resource, result);
		}
	};
}

