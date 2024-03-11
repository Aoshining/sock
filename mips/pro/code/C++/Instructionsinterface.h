#pragma once
#include"Instructions.h"

__declspec(dllexport) void Register(int i, char* output);
__declspec(dllexport) bool Operate(char* input);
__declspec(dllexport) void Clear();
