#include "FunctionCaller.h"

int FunctionCaller::callFunctionStaticDll(DWORD pid)
{
	TReplaceData* replaceFunction = NULL;
	replaceFunction = staticImport();
	return makeCall(pid, replaceFunction);
}

int FunctionCaller::callFunctionDynamicDll(DWORD pid)
{
	TReplaceData* replaceFunction = NULL;
	replaceFunction = dynamicImport();
	return makeCall(pid, replaceFunction);
}

int FunctionCaller::makeCall(DWORD pid, TReplaceData replaceFunction)
{
	if (replaceFunction != NULL)
	{
		replaceFunction(pid, SEARCH_STR, sizeof(SEARCH_STR), REPLACEMENT_STR, sizeof(REPLACEMENT_STR));
		return 1;
	}
	else
	{
		puts("\nDLL isn't found");
		return 0;
	}
}

TReplaceData* FunctionCaller::staticImport()
{
    return (TReplaceData*)ReplaceData;
}

TReplaceData* FunctionCaller::dynamicImport()
{
	HMODULE hDLL = LoadLibraryA(DLL);
	if (hDLL == NULL)
	{
		return NULL;
	}

	TReplaceData* replaceFunction = (TReplaceData*)GetProcAddress(hDLL, "ReplaceData");
	FreeLibrary(hDLL);
	return replaceFunction;
}

void FunctionCaller::injectLibrary(DWORD pid)
{
	HMODULE hDLL = LoadLibraryA("Kernel32.dll");
	LPLoadLibrary LoadLibraryA = (LPLoadLibrary)GetProcAddress(hDLL, "LoadLibraryA");

	HANDLE hProc = OpenProcess(PROCESS_VM_READ | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_CREATE_THREAD | PROCESS_CREATE_PROCESS, FALSE, pid);
	LPVOID path = VirtualAllocEx(hProc, NULL, strlen(INJECTED_DLL) + 1, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	int err = WriteProcessMemory(hProc, path, INJECTED_DLL, strlen(INJECTED_DLL) + 1, NULL);

	DWORD threadID;
	HANDLE HThread = CreateRemoteThread(hProc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryA, (LPVOID)path, NULL, &threadID);
	if (HThread == NULL)
	{
		printf("Error\n");
	}
	else
	{
		WaitForSingleObject(HThread, INFINITE);
	}

	FreeLibrary(hDLL);
	CloseHandle(hProc);
}
