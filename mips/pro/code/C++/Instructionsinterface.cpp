#include "Instructionsinterface.h"
#include"Instructions.h"
#include"assemble.h"

extern Information R;

void Register(int i, char* output) {
	if (i < 32) {
		const char* out= R.r[i].data();
		strcpy(output, out);
	}
	else if (i == 32) {
		const char* out = R.PC.data();
		strcpy(output, out);
	}
	else if (i > 32 && i < 38) {
		const char* out = R.memory[i-33].data();
		strcpy(output, out);
	}
}

bool Operate(char* in) {
	Instructions temp;
	int k = temp.interface_instruction(in);
	if (k == 0)
		return false;
	else
		return true;
}

void Clear() {
	for (int i = 0; i < 28; i++)
		R.r[i] = "00000000";
	//���¼Ĵ�����Ϊ��ֵ����ı䣨ò��������$sp�仯��
	R.r[1] = "20000000";
	R.r[28] = "10008000";//$gp
	R.r[29] = "7ffffffc";//$sp
	R.r[30] = "ffffffff";//$fp
	R.r[31] = "00000000";//&ra
	R.PC = "00400000";//PCÿ���ƶ���4 ֱ����Ϊ��һ��ָ��ĵ�ַ
	//Pc+4 ������ֱ��д��ÿ������������
	//memory
	//memory �׵�ַΪ "20000000"
	for (int i = 0; i < 5; i++)
		R.memory[i] = "00001000";
}