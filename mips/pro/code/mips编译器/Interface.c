#include "Interface.h"
__declspec(dllexport)int Add(int x, int y)
{
	return x + y;
}
__declspec(dllexport)char* SayHi(char* str)//C#中指针用^表示
{
	return str;
}
