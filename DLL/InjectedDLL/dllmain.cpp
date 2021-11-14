#include "../DLL/lib.h"

#define SEARCH_STR "String"
#define REPLACEMENT_STR "Replacement string"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdReson, LPVOID lpReserved)
{
	DWORD pid = GetCurrentProcessId();

	switch (fwdReson)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		ReplaceData(pid, SEARCH_STR, sizeof(SEARCH_STR), REPLACEMENT_STR, sizeof(REPLACEMENT_STR));
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}