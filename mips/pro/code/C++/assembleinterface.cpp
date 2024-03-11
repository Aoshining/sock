#include "assembleinterface.h"

void assembl(char* strin, char* output) {
	Assemble a;
	std::string out = a.interface_ass(strin);
	const char* out1 = out.data();
	strcpy(output, out1);
}

void disassembl(char* strin, char* output) {
	Disassemble d;
	std::string out = d.interface_dis(strin);
	const char* out1 = out.data();
	strcpy(output, out1);
}

void InitPC() {
	Assemble a;
	a.init_pc();
}