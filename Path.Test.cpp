#include "WindowsInclude.h"
#include "Path.h"
#include "Exception.h"
#include <cstring>
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(PathTest)
	{
	public:
		PathTest()
		{
		}

		TEST_METHOD(GetModuleFileName_Valid)
		{
			const auto module = reinterpret_cast<HMODULE>(1);
			API_MOCK(::GetModuleFileName) mock(
				[=](HMODULE m, char* b, unsigned long l)
				{
					Assert.AreEqual(module, m);
					Assert.IsNotNull(b);
					Assert.AreEqual(4096, l);
					std::strcpy(b, "result");
					return 1;
				});
			auto result = Path::GetModuleFileName(module);
			Assert.AreEqual("result", result);
		}

		TEST_METHOD(GetModuleFileName_Exception)
		{
			API_MOCK(::GetModuleFileName) mock(
				[](HMODULE,char*,unsigned long)
				{
					return 0;
				});
			Assert.ThrowsType<Exception>(
				[]{ Path::GetModuleFileName(); },
				[](const Exception& exception)
				{
					Assert.AreEqual(
						"GetModuleFileName",
						exception.GetLocation());
				});
		}

		TEST_METHOD(GetFileName_NoSlash)
		{
			const std::string value{ "noslash" };
			Assert.AreEqual(value, Path::GetFileName(value));
		}

		TEST_METHOD(GetFileName_EndsInSlash)
		{
			Assert.IsEmpty(Path::GetFileName("something\\"));
		}

		TEST_METHOD(GetFileName_WithSlash)
		{
			const std::string value{ "filename" };
			Assert.AreEqual(value, Path::GetFileName("something\\" + value));
		}

		TEST_METHOD(GetPath_NoSlash)
		{
			Assert.IsEmpty(Path::GetPath("noslash"));
		}

		TEST_METHOD(GetPath_StartsWithSlash)
		{
			Assert.IsEmpty(Path::GetPath("\\something"));
		}

		TEST_METHOD(GetPath_WithSlash)
		{
			Assert.AreEqual("path", Path::GetPath("path\\filename"));
		}

		TEST_METHOD(GetLastFolder)
		{
			Assert.AreEqual("last", Path::GetLastFolder("first\\last\\file"));
		}

		TEST_METHOD(GetTitle_NoDot)
		{
			Assert.AreEqual("title", Path::GetTitle("path\\title"));
		}

		TEST_METHOD(GetTitle_EndsWithDot)
		{
			Assert.AreEqual("title", Path::GetTitle("path\\title."));
		}

		TEST_METHOD(GetTitle_WithDot)
		{
			Assert.AreEqual("title.more", Path::GetTitle("path\\title.more.ext"));
		}

		TEST_METHOD(GetTitle_StartsWithDot)
		{
			Assert.IsEmpty(Path::GetTitle("path\\.ext"));
		}

		TEST_METHOD(GetExtension_NoDot)
		{
			Assert.IsEmpty(Path::GetExtension("path\\title"));
		}

		TEST_METHOD(GetExtension_EndsWithDot)
		{
			Assert.IsEmpty(Path::GetExtension("path\\title."));
		}

		TEST_METHOD(GetExtension_WithDot)
		{
			Assert.AreEqual("ext", Path::GetExtension("path\\title.more.ext"));
		}

		TEST_METHOD(GetExtension_StartsWithDot)
		{
			Assert.AreEqual("ext", Path::GetExtension("path\\.ext"));
		}

		TEST_METHOD(Combine_EmptyPath1)
		{
			Assert.AreEqual("path2", Path::Combine("", "path2"));
		}

		TEST_METHOD(Combine_EmptyPath2)
		{
			Assert.AreEqual("path1", Path::Combine("path1", ""));
		}

		TEST_METHOD(Combine_AddMissingSlash)
		{
			Assert.AreEqual("path1\\path2", Path::Combine("path1", "path2"));
		}

		TEST_METHOD(Combine_RemoveExtraSlash)
		{
			Assert.AreEqual("path1\\path2", Path::Combine("path1\\", "\\path2"));
		}

		TEST_METHOD(Combine_UseSlashFromPath1)
		{
			Assert.AreEqual("path1\\path2", Path::Combine("path1\\", "path2"));
		}

		TEST_METHOD(Combine_UseSlashFromPath2)
		{
			Assert.AreEqual("path1\\path2", Path::Combine("path1", "\\path2"));
		}
	};
}

