#include"num.h"

__declspec(dllexport)void myInt(char* number, int source, int target, int expand,char*output);
__declspec(dllexport)void intDouble(char* number, char* source, char* output);
__declspec(dllexport)void intFloat(char* number, char* source, char* output);
__declspec(dllexport)void intCompute(char* number1, char* number2, int source, int target, int expand, int compute,char*output);
__declspec(dllexport)void doubleCompute(char* number1, char* number2, char* source, int compute,char*output);
__declspec(dllexport)void floatCompute(char* number1, char* number2, char* source, int compute,char*output);
__declspec(dllexport)void decCompute(char* number1, char* number2, char* source, int compute, char* output);
__declspec(dllexport)void intDec(char* number, char* source, char* output);