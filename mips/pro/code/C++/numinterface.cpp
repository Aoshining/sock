#include "numinterface.h"

void myInt(char* number, int source, int target, int expand, char* output) {
	Num n;
	string out = n.Int(number, source, target, expand);
	const char* out1 = out.data();
	strcpy(output, out1);

}

void intFloat(char* number, char* source, char* output)
{
	Num n;
	string out = n.Dec(number, source);
	const char* out1 = out.data();
	string out2 = n.Float((char*)out1, 10);
	const char* out3 = out2.data();
	strcpy(output, out3);
}

void intDouble(char* number, char* source, char* output)
{
	Num n;
	string out = n.Dec(number, source);
	const char* out1 = out.data();
	string out2 = n.Double((char*)out1, 10);
	const char* out3 = out2.data();
	strcpy(output, out3);
}

void intCompute(char* number1, char* number2, int source, int target, int expand, int compute, char* output) {
	Num n;
	string out = n.IntCompute(number1, number2, source, target, expand, compute);
	const char* out1 = out.data();
	strcpy(output, out1);
}

void doubleCompute(char* number1, char* number2, char* source, int compute, char* output) {
	Num n;
	string num1 = n.Dec(number1, source), num2 = n.Dec(number2, source);
	string out = n.DoubleCompute((char*)num1.c_str(), (char*)num2.c_str(), 10, compute);
	const char* out1 = out.data();
	strcpy(output, out1);
}

void floatCompute(char* number1, char* number2, char* source, int compute, char* output) {
	Num n;
	string num1 = n.Dec(number1, source), num2 = n.Dec(number2, source);
	string out = n.FloatCompute((char*)num1.c_str(), (char*)num2.c_str(), 10, compute);
	const char* out1 = out.data();
	strcpy(output, out1);
}

void decCompute(char* number1, char* number2, char* source, int compute, char* output) {
	Num n;
	string out = n.DecCompute(number1, number2, source, compute);
	const char* out1 = out.data();
	strcpy(output, out1);
}

void intDec(char* number, char* source, char* output)
{
	Num n;
	string out = n.Dec(number, source);
	const char* out1 = out.data();
	strcpy(output, out1);
}