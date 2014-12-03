#include "WindowsInclude.h"
#include "ProcessInstance.h"
#include "WindowsException.h"

namespace Wex
{
	void ProcessInstance::Initialize(HINSTANCE handle)
	{
		GetSingleton().handle = handle;
		InitializeAllCommonControls();
	}
	
	HINSTANCE ProcessInstance::Get()
	{
		return GetSingleton().handle;
	}
	
	ProcessInstance& ProcessInstance::GetSingleton()
	{
		static ProcessInstance singleton;
		return singleton;
	}
	
	void ProcessInstance::InitializeAllCommonControls()
	{
		INITCOMMONCONTROLSEX data;
		data.dwSize = sizeof(data);
		data.dwICC =
			ICC_ANIMATE_CLASS |
			ICC_BAR_CLASSES |
			ICC_COOL_CLASSES |
			ICC_DATE_CLASSES |
			ICC_HOTKEY_CLASS |
			ICC_INTERNET_CLASSES |
			ICC_LISTVIEW_CLASSES |
			ICC_LINK_CLASS |
			ICC_NATIVEFNTCTL_CLASS |
			ICC_PAGESCROLLER_CLASS |
			ICC_PROGRESS_CLASS |
			ICC_STANDARD_CLASSES |
			ICC_TAB_CLASSES |
			ICC_TREEVIEW_CLASSES |
			ICC_UPDOWN_CLASS |
			ICC_USEREX_CLASSES;
		auto result = ::InitCommonControlsEx(&data);
		CheckLastWindowsError(!result, "InitCommonControlsEx");
	}
}

