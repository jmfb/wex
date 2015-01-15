#include "Range.h"
#include <UnitTest/UnitTest.h>
using UnitTest::Assert;

namespace Wex
{
	TEST_CLASS(RangeTest)
	{
	public:
		RangeTest()
		{
		}

		TEST_METHOD(IndexRange)
		{
			std::vector<int> values{ 1, 2, 3, 4 };
			auto sum = 0;
			for (auto index: Indexes(values.size()))
				sum += values[index];
			Assert.AreEqual(10, sum);
		}
	};
}

