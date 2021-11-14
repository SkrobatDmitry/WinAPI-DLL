#define _CRT_SECURE_NO_WARNINGS
#include "FunctionCaller.h"

int main(int argc, char* argv[])
{
	_CrtSetDebugFillThreshold(0);

	const char data1[] = SEARCH_STR;
	const char data2[] = SEARCH_STR;
	const char replacement[] = REPLACEMENT_STR;

	DWORD pid = GetCurrentProcessId();
	printf("Current pid: %d\n", pid);

	printf("0 - Static | 1 - Dynamic | 2 - Remote thread\nEnter DLL: ");
	char c = getchar();

	FunctionCaller caller;
	switch (c)
	{
	case '0':
		caller.callFunctionStaticDll(pid);
		break;
	case '1':
		caller.callFunctionDynamicDll(pid);
		break;
	case '2':
		printf("\nEnter pid: ");

		DWORD injectionPid;
		scanf("%d", &injectionPid);

		caller.injectLibrary(injectionPid);
		break;
	default:
		break;
	}

	printf("\nOriginal Data1 string: \"%s\" | The resulting Data1 string: \"%s\"\nOriginal Data2 string: \"%s\" | The resulting Data2 string: \"%s\"\n", 
		SEARCH_STR, data1, SEARCH_STR, data2);

	return 0;
}
