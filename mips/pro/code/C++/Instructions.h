#pragma once
#include<iostream>
#include<stdio.h>
#include <cstdio> 
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;

struct Information {
    string r[32];
    string PC;
    string memory[5];
    Information() {
        //0-26 ��ʼ��Ϊ0
        //$zeor $v0-$v1 $a0-$a3 $t0-$t9 $s0-$s7 $k0-$k1����0
        for (int i = 0; i < 28; i++)
            r[i] = "00000000";
        //���¼Ĵ�����Ϊ��ֵ����ı䣨ò��������$sp�仯��
        r[1] = "20000000";
        r[28] = "10008000";//$gp
        r[29] = "7ffffffc";//$sp
        r[30] = "ffffffff";//$fp
        r[31] = "00000000";//&ra
        PC = "00400000";//PCÿ���ƶ���4 ֱ����Ϊ��һ��ָ��ĵ�ַ
        //Pc+4 ������ֱ��д��ÿ������������
        //memory
        //memory �׵�ַΪ "20000000"
        for (int i = 0; i < 5; i++)
            memory[i] = "00001000";
    }
};

class Instructions {
	static void pcadd(int k);
	static string Int(char* number, int source, int target, int expand);
	static string complement(string k);
	static void ADD(int rs, int rt, int rd);
	static void SUB(int rs, int rt, int rd);
	static void OR(int rs, int rt, int rd);
	static void AND(int rs, int rt, int rd);
	static void NOR(int rs, int rt, int rd);
	static void ADDI(int rs, int rt, int immediate);
	static void SLL(int rs, int rt, int immediate);
	static void SRL(int rs, int rt, int immediate);
	static int BEQ(int rs, int rt, int immediate);
	static int BNE(int rs, int rt, int immediate);
	static void LW(int rs, int rt, int address);
	static void SW(int rs, int rt, int address);
	static int J(string address);
	static int JAL(string address);
	static int JR(int rs);
public:
    static int interface_instruction(char str[]);
};