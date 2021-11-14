#pragma once
#include <windows.h>
#include "../DLL/lib.h"

#define DLL "DLL.dll"
#define INJECTED_DLL "InjectedDLL.dll"

#define SEARCH_STR "THIS SHOUD BE REPLACED"
#define REPLACEMENT_STR "REPLACED STRING"

typedef void _stdcall TReplaceData(DWORD pid, const char* data, size_t len, const char* replacement, size_t replacementLen);

typedef HMODULE(WINAPI* LPLoadLibrary)(LPCSTR);
typedef HMODULE(WINAPI* LPGetProcAddress)(HMODULE, LPCSTR);

class FunctionCaller
{
public:
	int callFunctionStaticDll(DWORD pid);
	int callFunctionDynamicDll(DWORD pid);
	void injectLibrary(DWORD pid);

private:
	int makeCall(DWORD pid, TReplaceData replaceFunction);
	TReplaceData* staticImport();
	TReplaceData* dynamicImport();
};

