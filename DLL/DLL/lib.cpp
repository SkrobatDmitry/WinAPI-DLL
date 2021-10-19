#include "lib.h"

EXPORT BOOL WINAPI ReplaceStringInVM(DWORD pid, const char* oldStr, const char* newStr)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
	if (!hProcess)
	{
		return NULL;
	}
		
	LPCVOID lpAddress = (LPCVOID)0;
	MEMORY_BASIC_INFORMATION vmInfo;

	while (VirtualQueryEx(hProcess, lpAddress, &vmInfo, sizeof(vmInfo)) == sizeof(vmInfo))
	{
		
	}

	return TRUE;
}