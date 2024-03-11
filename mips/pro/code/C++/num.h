#include <iostream>
#include <cstdio> 
#include <cstdlib>
#include <cstring>
#include <cmath>
#include<string>

using namespace std;


class Num {
public:
	static string Int(char* number, int source, int target, int expand);
	static string Float(char* number, int source);
	static string Double(char* number, int source);
	static string Dec(char* number, char* source);
	static string IntCompute(char* number1, char* number2, int source, int target, int expand, int compute);
	static string DecCompute(char* number1, char* number2, char* source, int compute);
	static string FloatCompute(char* number1, char* number2, int source, int compute);
	static string DoubleCompute(char* number1, char* number2, int source, int compute);
};
