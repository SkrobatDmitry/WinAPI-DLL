#pragma once
#include <windows.h>
#include <vector>

#define EXPORT extern "C" void __declspec(dllexport)
EXPORT _stdcall ReplaceData(DWORD pid, const char* data, size_t len, const char* replacement, size_t replacementLen);
