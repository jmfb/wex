#include <windows.h>

extern "C" BOOL __stdcall DllMain(
	HINSTANCE instance,
	unsigned long reason,
	void* reserved)
{
	return TRUE;
}

