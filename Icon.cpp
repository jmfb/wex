#include "WindowsInclude.h"
#include "Icon.h"
#include "ProcessInstance.h"

namespace Wex
{
	HICON Icon::Load(int id, int width, int height)
	{
		auto result = ::LoadImage(
			ProcessInstance::Get(),
			MAKEINTRESOURCE(id),
			IMAGE_ICON,
			width,
			height,
			LR_DEFAULTCOLOR);
		return reinterpret_cast<HICON>(result);
	}

	HICON Icon::LoadLarge(int id)
	{
		return Load(
			id,
			::GetSystemMetrics(SM_CXICON),
			::GetSystemMetrics(SM_CYICON));
	}

	HICON Icon::LoadSmall(int id)
	{
		return Load(
			id,
			::GetSystemMetrics(SM_CXSMICON),
			::GetSystemMetrics(SM_CYSMICON));
	}
}

