#pragma once

namespace Wex
{
	class Flag
	{
	public:
		template <typename FlagsType, typename FlagType>
		static bool Test(FlagsType flags, FlagType flag)
		{
			return (flags & flag) == flag;
		}

	private:
		friend class FlagTest;
	};
}

