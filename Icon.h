#pragma once

namespace Wex
{
	class Icon
	{
	public:
		static HICON Load(int id, int width, int height);
		static HICON LoadLarge(int id);
		static HICON LoadSmall(int id);

	private:
		friend class IconTest;
	};
}

