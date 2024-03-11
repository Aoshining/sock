#include"Instructions.h"
#include "assemble.h"

Information R;
extern Label_Reg_Imme label_reg_imme;


void Instructions::pcadd(int k)
{
    char* stop;
    char* t1 = (char*)R.PC.data();
    unsigned int a = strtoul(t1, &stop, 16);
    a = a + k;
    char integer1[100] = { 0 };
    itoa(a, integer1, 16);
    string tnum1 = integer1;
    int expand = 8;
    if (expand)
    {
        if (tnum1.length() < expand)
            tnum1.insert(0, expand - tnum1.length(), '0');
        else if (tnum1.length() > expand)
            tnum1.erase(0, tnum1.length() - expand);
    }
    R.PC = tnum1;
}
string Instructions::Int(char* number, int source, int target, int expand)
{
    char* stop;
    unsigned int i = strtoul(number, &stop, source);
    if (*stop != '\0')
    {
        cout << "Not a valid integer." << endl;
        return 0;
    }
    char integer[100] = { 0 };
    itoa(i, integer, target);
    string tnum = integer;
    if (expand)
    {
        if (tnum.length() < expand)
            tnum.insert(0, expand - tnum.length(), '0');
        else if (tnum.length() > expand)
            tnum.erase(0, tnum.length() - expand);
    }
    return tnum;
}
string Instructions::complement(string k) //k �� 32bits ������
{
    for (int i = 0; i < 32; i++)
    {
        if (k[i] == '0')
            k[i] = '1';
        else
            k[i] = '0';
    }
    char* stop;
    char* t1 = (char*)k.data();
    unsigned int a = strtoul(t1, &stop, 2);
    a = a + 1;
    char integer[100] = { 0 };
    itoa(a, integer, 16);
    string tnum = integer;
    int expand = 8;
    if (expand)
    {
        if (tnum.length() < expand)
            tnum.insert(0, expand - tnum.length(), '0');
        else if (tnum.length() > expand)
            tnum.erase(0, tnum.length() - expand);
    }
    return tnum;
}
void Instructions::ADD(int rs, int rt, int rd)
{
    pcadd(4);
    char* stop;
    char* t1 = (char*)R.r[rt].data();
    unsigned int a = strtoul(t1, &stop, 16);
    char* t2 = (char*)R.r[rd].data();
    unsigned int b = strtoul(t2, &stop, 16);
    unsigned int result = a + b;
    char integer[100] = { 0 };
    itoa(result, integer, 16);
    string tnum = integer;
    int expand = 8;
    if (expand)
    {
        if (tnum.length() < expand)
            tnum.insert(0, expand - tnum.length(), '0');
        else if (tnum.length() > expand)
            tnum.erase(0, tnum.length() - expand);
    }
    R.r[rs] = tnum;
}
void Instructions::SUB(int rs, int rt, int rd)
{
    char* t2 = (char*)R.r[rd].data();
    string rd2 = Int(t2, 16, 2, 32);
    string ird = complement(rd2);
    rd2 = R.r[rd];
    R.r[rd] = ird;
    //����ADD Pc�Ѿ�+4
    ADD(rs, rt, rd);
    R.r[rd] = rd2;
}
void Instructions::OR(int rs, int rt, int rd)
{
    pcadd(4);
    char* t1 = (char*)R.r[rt].data();
    string rt2 = Int(t1, 16, 2, 32);
    char* t2 = (char*)R.r[rd].data();
    string rd2 = Int(t2, 16, 2, 32);
    char rs2[33];
    for (int i = 0; i < 32; i++)
    {
        if (rt2[i] == '0' && rd2[i] == '0')
            rs2[i] = '0';
        else
            rs2[i] = '1';
    }
    rs2[32] = '\0';
    string k = rs2;
    R.r[rs] = Int(rs2, 2, 16, 8);
}
void Instructions::AND(int rs, int rt, int rd)
{
    pcadd(4);
    char* t1 = (char*)R.r[rt].data();
    string rt2 = Int(t1, 16, 2, 32);
    char* t2 = (char*)R.r[rd].data();
    string rd2 = Int(t2, 16, 2, 32);
    char rs2[33];
    for (int i = 0; i < 32; i++)
    {
        if (rt2[i] == '1' && rd2[i] == '1')
            rs2[i] = '1';
        else
            rs2[i] = '0';
    }
    rs2[32] = '\0';
    string k = rs2;
    R.r[rs] = Int(rs2, 2, 16, 8);
}
void Instructions::NOR(int rs, int rt, int rd)
{
    pcadd(4);
    char* t1 = (char*)R.r[rt].data();
    string rt2 = Int(t1, 16, 2, 32);
    char* t2 = (char*)R.r[rd].data();
    string rd2 = Int(t2, 16, 2, 32);
    char rs2[33];
    for (int i = 0; i < 32; i++)
    {
        if (rt2[i] == '0' && rd2[i] == '0')
            rs2[i] = '1';
        else
            rs2[i] = '0';
    }
    rs2[32] = '\0';
    string k = rs2;
    R.r[rs] = Int(rs2, 2, 16, 8);
}
void Instructions::ADDI(int rs, int rt, int immediate)
{
    pcadd(4);
    char* stop;
    char* t1 = (char*)R.r[rt].data();
    unsigned int a = strtoul(t1, &stop, 16);
    unsigned int result = a + immediate;
    char integer1[100] = { 0 };
    itoa(result, integer1, 16);
    string tnum1 = integer1;
    int expand = 8;
    if (expand)
    {
        if (tnum1.length() < expand)
            tnum1.insert(0, expand - tnum1.length(), '0');
        else if (tnum1.length() > expand)
            tnum1.erase(0, tnum1.length() - expand);
    }
    R.r[rs] = tnum1;
}
void Instructions::SLL(int rs, int rt, int immediate)
{
    if (immediate < 0)
    {
        cout << "ERROR" << endl;
        return;
    }
    pcadd(4);
    char* stop;
    char* t1 = (char*)R.r[rt].data();
    unsigned int a = strtoul(t1, &stop, 16);
    a = a << immediate;
    char integer[100] = { 0 };
    itoa(a, integer, 16);
    string tnum = integer;
    int expand = 8;
    if (expand)
    {
        if (tnum.length() < expand)
            tnum.insert(0, expand - tnum.length(), '0');
        else if (tnum.length() > expand)
            tnum.erase(0, tnum.length() - expand);
    }
    R.r[rs] = tnum;
}
void Instructions::SRL(int rs, int rt, int immediate)
{
    if (immediate < 0)
    {
        cout << "ERROR" << endl;
        return;
    }
    pcadd(4);
    char* stop;
    char* t1 = (char*)R.r[rt].data();
    unsigned int a = strtoul(t1, &stop, 16);
    a = a >> immediate;
    char integer[100] = { 0 };
    itoa(a, integer, 16);
    string tnum = integer;
    int expand = 8;
    if (expand)
    {
        if (tnum.length() < expand)
            tnum.insert(0, expand - tnum.length(), '0');
        else if (tnum.length() > expand)
            tnum.erase(0, tnum.length() - expand);
    }
    R.r[rs] = tnum;
}
int Instructions::BEQ(int rs, int rt, int immediate)
{
    pcadd(4);
    if (R.r[rs] == R.r[rt])
    {
        pcadd(immediate * 4);
        return immediate;
    }
    else
        return 0;
}
int Instructions::BNE(int rs, int rt, int immediate)
{
    pcadd(4);
    if (R.r[rs] != R.r[rt])
    {
        pcadd(immediate * 4);
        return immediate;
    }
    else
        return 0;

}
void Instructions::LW(int rs, int rt, int address)
{
    pcadd(4);
    if (address % 4 != 0)
    {
        cout << "warning: recommend you enter multiples of four" << endl;
        return;
    }
    char* stop;
    char* t1 = (char*)R.r[rt].data();
    unsigned int a = strtoul(t1, &stop, 16);
    a = a + address;
    char integer1[100] = { 0 };
    itoa(a, integer1, 16);
    string tnum1 = integer1;
    int expand = 8;
    if (expand)
    {
        if (tnum1.length() < expand)
            tnum1.insert(0, expand - tnum1.length(), '0');
        else if (tnum1.length() > expand)
            tnum1.erase(0, tnum1.length() - expand);
    }
    if (tnum1 == "20000000")
        R.r[rs] = R.memory[0];
    else if (tnum1 == "20000004")
        R.r[rs] = R.memory[1];
    else if (tnum1 == "20000008")
        R.r[rs] = R.memory[2];
    else if (tnum1 == "2000000c")
        R.r[rs] = R.memory[3];
    else if (tnum1 == "20000010")
        R.r[rs] = R.memory[4];
    else
        cout << "Sorry for out of readable memory" << endl;
}
void Instructions::SW(int rs, int rt, int address)
{
    pcadd(4);
    if (address % 4 != 0)
    {
        cout << "warning: recommend you enter multiples of four" << endl;
        return;
    }
    char* stop;
    char* t1 = (char*)R.r[rt].data();
    unsigned int a = strtoul(t1, &stop, 16);
    a = a + address;
    char integer1[100] = { 0 };
    itoa(a, integer1, 16);
    string tnum1 = integer1;
    int expand = 8;
    if (expand)
    {
        if (tnum1.length() < expand)
            tnum1.insert(0, expand - tnum1.length(), '0');
        else if (tnum1.length() > expand)
            tnum1.erase(0, tnum1.length() - expand);
    }
    if (tnum1 == "20000000")
        R.memory[0] = R.r[rs];
    else if (tnum1 == "20000004")
        R.memory[1] = R.r[rs];
    else if (tnum1 == "20000008")
        R.memory[2] = R.r[rs];
    else if (tnum1 == "2000000c")
        R.memory[3] = R.r[rs];
    else if (tnum1 == "20000010")
        R.memory[4] = R.r[rs];
    else
        cout << "Sorry for out of readable memory" << endl;
}
int Instructions::J(string address)
{
    char* stop;
    char* t = (char*)address.data();
    unsigned int ad = strtoul(t, &stop, 2);
    pcadd(4);
    ad = ad << 2;
    char integer[100] = { 0 };
    itoa(ad, integer, 16);
    string tnum = integer;
    int expand = 7;
    if (expand)
    {
        if (tnum.length() < expand)
            tnum.insert(0, expand - tnum.length(), '0');
        else if (tnum.length() > expand)
            tnum.erase(0, tnum.length() - expand);
    }
    cout << R.PC << endl;
    char* t1 = (char*)R.PC.data();
    unsigned int a = strtoul(t1, &stop, 16);
    R.PC = R.PC[0] + tnum;
    cout << R.PC << endl;
    char* t2 = (char*)R.PC.data();
    unsigned int b = strtoul(t2, &stop, 16);
    b = (b - a) / 4;
    return b;
}
int Instructions::JAL(string address)
{
    pcadd(4);
    R.r[31] = R.PC;
    pcadd(-4);
    return J(address);
}
int Instructions::JR(int rs)
{
    pcadd(4);
    char* stop;
    char* t = (char*)R.r[rs].data();
    unsigned int a = strtoul(t, &stop, 16);
    char* t1 = (char*)R.PC.data();
    unsigned int b = strtoul(t, &stop, 16);
    R.PC = R.r[rs];
    return (b - a) / 4;
}

int Instructions::interface_instruction(char str[])
{
    Assemble temp;
    temp.interface_ass(str);
    if (label_reg_imme.op == "add")
    {
        ADD(label_reg_imme.r1, label_reg_imme.r2, label_reg_imme.r3);
        return 1;
    }
    else if (label_reg_imme.op == "sub")
    {
        SUB(label_reg_imme.r1, label_reg_imme.r2, label_reg_imme.r3);
        return 1;
    }
    else if (label_reg_imme.op == "or")
    {
        OR(label_reg_imme.r1, label_reg_imme.r2, label_reg_imme.r3);
        return 1;
    }
    else if (label_reg_imme.op == "and")
    {
        AND(label_reg_imme.r1, label_reg_imme.r2, label_reg_imme.r3);
        return 1;
    }
    else if (label_reg_imme.op == "nor")
    {
        NOR(label_reg_imme.r1, label_reg_imme.r2, label_reg_imme.r3);
        return 1;
    }
    else if (label_reg_imme.op == "addi")
    {
        ADDI(label_reg_imme.r1, label_reg_imme.r2, label_reg_imme.immediate);
        return 1;
    }
    else if (label_reg_imme.op == "sll")
    {
        SLL(label_reg_imme.r1, label_reg_imme.r2, label_reg_imme.immediate);
        return 1;
    }
    else if (label_reg_imme.op == "srl")
    {
        SRL(label_reg_imme.r1, label_reg_imme.r2, label_reg_imme.immediate);
        return 1;
    }
    else if (label_reg_imme.op == "beq")
    {
        BEQ(label_reg_imme.r1, label_reg_imme.r2, label_reg_imme.immediate);
        return 1;
    }
    else if (label_reg_imme.op == "bne")
    {
        BNE(label_reg_imme.r1, label_reg_imme.r2, label_reg_imme.immediate);
        return 1;
    }
    else if (label_reg_imme.op == "lw")
    {
        LW(label_reg_imme.r1, label_reg_imme.r2, label_reg_imme.immediate);
        return 1;
    }
    else if (label_reg_imme.op == "sw")
    {
        SW(label_reg_imme.r1, label_reg_imme.r2, label_reg_imme.immediate);
        return 1;
    }
    else if (label_reg_imme.op == "j")
    {
        J(label_reg_imme.jump);
        return 1;
    }
    else if (label_reg_imme.op == "jal")
    {
        JAL(label_reg_imme.jump);
        return 1;
    }
    else if(label_reg_imme.op == "jr")
    {
        JR(label_reg_imme.r1);
        return 1;
    }
    else
        return 0;
}