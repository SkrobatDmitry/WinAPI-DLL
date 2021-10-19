#pragma once
#include <windows.h>
#define EXPORT extern "C" __declspec(dllexport)

EXPORT BOOL WINAPI ReplaceStringInVM(DWORD pid, const char* oldStr, const char* newStr);