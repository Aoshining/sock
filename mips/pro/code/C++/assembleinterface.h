#include"disassemble.h"
#include"assemble.h"

__declspec(dllexport)void assembl(char* strin, char* output);
__declspec(dllexport)void disassembl(char* strin, char* output);
__declspec(dllexport)void InitPC();