#include"assemble.h"
#include"instructions.h"
#include<vector>
#include <algorithm>

extern Information R;

std::vector<std::string> my_label;
std::vector<std::string> my_pc;

Label_Reg_Imme label_reg_imme;

// MIPSָ��ṹ��
struct Instruction_R {
    unsigned int opcode : 6;
    unsigned int rs : 5;
    unsigned int rt : 5;
    unsigned int rd : 5;
    unsigned int shamt : 5;
    unsigned int funct : 6;
};

struct Instruction_I {
    unsigned int opcode : 6;
    unsigned int rs : 5;
    unsigned int rt : 5;
    unsigned int immediate : 16;
};

struct Instruction_J {
    unsigned int opcode : 6;
    unsigned int address : 26;
};

enum In_R {
    sll, srl = 2, jr = 8, add = 32, sub = 34,
    and_op = 36, or_op, nor = 39
};

enum In_I {
    beq = 4, bne, addi = 8, ori = 13, lui = 15,
    lw = 35, sw = 43
};

enum In_J {
    j = 2, jal = 12
};

std::string registers[32] = {
    "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
    "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
    "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
    "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"
};

bool Assemble::is_R(const std::string& operator_str) {
    return (operator_str == "sll" || operator_str == "srl" || operator_str == "jr" ||
        operator_str == "add" || operator_str == "sub" || operator_str == "and" ||
        operator_str == "or" || operator_str == "nor");
}

bool Assemble::is_I(const std::string& operator_str) {
    return (operator_str == "beq" || operator_str == "bne" || operator_str == "addi" ||
        operator_str == "ori" || operator_str == "lui" || operator_str == "lw" ||
        operator_str == "sw");
}

bool Assemble::is_J(const std::string& operator_str) {
    return (operator_str == "j" || operator_str == "jal");
}

std::string Assemble::deTobin(int decimal, int length) {
    std::string binaryStr;
    if (decimal == 0) {
        binaryStr = std::string(length, '0'); // ����0���⴦��
    }
    else {
        while (decimal > 0) {
            int remainder = decimal % 2;
            binaryStr = std::to_string(remainder) + binaryStr;
            decimal = decimal / 2;
        }
        if (binaryStr.length() < length) {
            binaryStr = std::string(length - binaryStr.length(), '0') + binaryStr;
        }
    }
    return binaryStr;
}
void Assemble::ass_R(std::string& instruction, const std::string& operator_str, std::string& binary) {
    int is_error = 0;
    int shamt = 0, funct, rs, rt, rd, i, j;
    std::string reg;
    if (operator_str == "jr") {
        funct = jr;
        shamt = 0;
        rt = 0;
        rd = 0;
        reg = instruction;

        for (j = 0; j < 32; j++) {
            if (registers[j] == reg)
                break;
        }
        if (j >= 32)
        {
            binary = "++";
            return;
        }
        rs = j;
    }
    else if (operator_str == "sll" || operator_str == "srl") {

        size_t firstCommaPos = instruction.find(',');
        if (firstCommaPos != std::string::npos) {
            size_t secondCommaPos = instruction.find(',', firstCommaPos + 1);
            if (secondCommaPos != std::string::npos) {
            }
            else {
                binary = "++";
                return;
            }
        }
        else {
            binary = "++";
            return;
        }

        if (operator_str == "sll")
            funct = sll;
        else if (operator_str == "srl")
            funct = srl;

        rs = 0;
        i = 0;
        while (instruction[i] != ',')
            i++;
        reg = instruction.substr(0, i);
        i++;
        while (instruction[i] == ' ')
            i++;
        for (j = 0; j < 32; j++) {
            if (registers[j] == reg)
                break;
        }
        if (j >= 32)
        {
            binary = "++";
            return;
        }
        rd = j;

        instruction = instruction.substr(i);
        i = 0;
        while (instruction[i] != ',')
            i++;

        reg = instruction.substr(0, i);
        i++;
        while (instruction[i] == ' ')
            i++;

        for (j = 0; j < 32; j++) {
            if (registers[j] == reg)
                break;
        }
        if (j >= 32)
        {
            binary = "++";
            return;
        }
        rt = j;

        instruction = instruction.substr(i);
        reg = instruction;
        j = 0;
        while (reg[j] != '\0') {
            shamt = 10 * shamt + (reg[j] - '0');
            j++;
        }
    }
    else {

        size_t firstCommaPos = instruction.find(',');
        if (firstCommaPos != std::string::npos) {
            size_t secondCommaPos = instruction.find(',', firstCommaPos + 1);
            if (secondCommaPos != std::string::npos) {
            }
            else {
                binary = "++";
                return;
            }
        }
        else {
            binary = "++";
            return;
        }

        shamt = 0;

        if (operator_str == "add")
            funct = add;
        else if (operator_str == "sub")
            funct = sub;
        else if (operator_str == "and")
            funct = and_op;
        else if (operator_str == "or")
            funct = or_op;
        else if (operator_str == "nor")
            funct = nor;
        else {
            binary = "++";
            return;
        }
        i = 0;
        while (instruction[i] != ',')
            i++;

        reg = instruction.substr(0, i);
        i++;
        while (instruction[i] == ' ')
            i++;

        for (j = 0; j < 32; j++) {
            if (registers[j] == reg)
                break;
        }
        if (j >= 32)
        {
            binary = "++";
            return;
        }
        rd = j;

        instruction = instruction.substr(i);
        i = 0;
        while (instruction[i] != ',')
            i++;

        reg = instruction.substr(0, i);
        i++;
        while (instruction[i] == ' ')
            i++;

        for (j = 0; j < 32; j++) {
            if (registers[j] == reg)
                break;
        }
        if (j >= 32)
        {
            binary = "++";
            return;
        }
        rs = j;

        instruction = instruction.substr(i);
        reg = instruction;

        for (j = 0; j < 32; j++) {
            if (registers[j] == reg)
                break;
        }
        if (j >= 32)
        {
            binary = "++";
            return;
        }
        rt = j;
    }

    label_reg_imme.r1 = rd;
    label_reg_imme.r2 = rs;
    label_reg_imme.r3 = rt;
    label_reg_imme.immediate = 0;
    label_reg_imme.jump = "0";

    Instruction_R inst;
    inst.opcode = 0;
    inst.rs = rs;
    inst.rt = rt;
    inst.rd = rd;
    inst.shamt = shamt;
    inst.funct = funct;

    binary = deTobin(inst.opcode, 6) + deTobin(inst.rs, 5) + deTobin(inst.rt, 5) +
        deTobin(inst.rd, 5) + deTobin(inst.shamt, 5) + deTobin(inst.funct, 6);
}

void Assemble::ass_I(std::string& instruction, const std::string& operator_str, std::string& binary) {
    int opcode, rs, rt, immediate = 0, i, j;
    std::string reg;

    if (operator_str == "lw" || operator_str == "sw") {

        size_t firstCommaPos = instruction.find('(');
        if (firstCommaPos != std::string::npos) {
            size_t secondCommaPos = instruction.find(')', firstCommaPos + 1);
            if (secondCommaPos != std::string::npos) {
            }
            else {
                binary = "++";
                return;
            }
        }
        else {
            binary = "++";
            return;
        }

        if (operator_str == "lw")
            opcode = lw;
        else
            opcode = sw;

        i = 0;
        while (instruction[i] != ',')
            i++;

        reg = instruction.substr(0, i);
        i++;
        while (instruction[i] == ' ')
            i++;

        for (j = 0; j < 32; j++) {
            if (registers[j] == reg)
                break;
        }
        if (j >= 32)
        {
            binary = "++";
            return;
        }
        rt = j;

        instruction = instruction.substr(i);
        i = 0;

        while (instruction[i] != '(')
            i++;

        reg = instruction.substr(0, i);
        i++;
        while (instruction[i] == ' ')
            i++;

        j = 0;
        while (reg[j] != '\0') {
            immediate = 10 * immediate + (reg[j] - '0');
            j++;
        }

        instruction = instruction.substr(i);
        i = 0;
        while (instruction[i] != ')')
            i++;

        reg = instruction.substr(0, i);

        for (j = 0; j < 32; j++) {
            if (registers[j] == reg)
                break;
        }
        if (j >= 32)
        {
            binary = "++";
            return;
        }
        rs = j;
    }
    else {
        if (operator_str == "lui") {
            size_t firstCommaPos = instruction.find(',');
            if (firstCommaPos == std::string::npos) {
                binary = "++";
                return;
            }
        }
        else {
            size_t firstCommaPos = instruction.find(',');
            if (firstCommaPos != std::string::npos) {
                size_t secondCommaPos = instruction.find(',', firstCommaPos + 1);
                if (secondCommaPos != std::string::npos) {
                }
                else {
                    binary = "++";
                    return;
                }
            }
            else {
                binary = "++";
                return;
            }
        }

        if (operator_str == "addi")
            opcode = addi;
        else if (operator_str == "ori")
            opcode = ori;
        else if (operator_str == "lui")
            opcode = lui;
        else if (operator_str == "beq")
            opcode = beq;
        else if (operator_str == "bne")
            opcode = bne;

        i = 0;
        while (instruction[i] != ',')
            i++;

        reg = instruction.substr(0, i);
        i++;
        while (instruction[i] == ' ')
            i++;

        for (j = 0; j < 32; j++) {
            if (registers[j] == reg)
                break;
        }
        if (j >= 32)
        {
            binary = "++";
            return;
        }
        rt = j;

        if (operator_str == "lui")
            rs = 0;
        else {
            instruction = instruction.substr(i);
            i = 0;
            while (instruction[i] != ',')
                i++;

            reg = instruction.substr(0, i);
            i++;
            while (instruction[i] == ' ')
                i++;

            for (j = 0; j < 32; j++) {
                if (registers[j] == reg)
                    break;
            }
            if (j >= 32)
            {
                binary = "++";
                return;
            }
            rs = j;
        }
        instruction = instruction.substr(i);
        reg = instruction;

        j = 0;
        while (reg[j] != '\0') {
            immediate = 10 * immediate + (reg[j] - '0');
            j++;
        }
    }

    label_reg_imme.r1 = rt;
    label_reg_imme.r2 = rs;
    label_reg_imme.r3 = 0;
    label_reg_imme.immediate = immediate;
    label_reg_imme.jump = "0";

    Instruction_I inst;
    inst.opcode = opcode;
    inst.rs = rs;
    inst.rt = rt;
    inst.immediate = immediate;

    binary = deTobin(inst.opcode, 6) + deTobin(inst.rs, 5) + deTobin(inst.rt, 5) +
        deTobin(inst.immediate, 16);
}

void Assemble::ass_J(std::string& instruction, const std::string& operator_str, std::string& binary) {
    int opcode, address = 0, i;
    std::string reg;

    if (operator_str == "j") {
        opcode = j;
        reg = instruction;
        i = 0;

        while (reg[i] != '\0') {
            if(reg[i] > '9' || reg[i] < '0')
                break;
            i++;
        }
        if(reg[i] == '\0'){
            i = 0;
            while (reg[i] != '\0') {
                address = 10 * address + (reg[i] - '0');
                i++;
            }
        }
        else{
            std::string pp;
            auto it = std::find(my_label.begin(), my_label.end(), reg);
            if (it != my_label.end()) {
                pp = my_pc[it - my_label.begin()];
                pp = pp.substr(1);
                int decimalNumber = std::stoi(pp, 0, 16);
                address = decimalNumber/4;
            } else {
                binary = "++";
                return;
            }
        }
    }
    else {
        opcode = jal;
        reg = instruction;
        i = 0;

       while (reg[i] != '\0') {
            if(reg[i] > '9' || reg[i] < '0')
                break;
            i++;
        }
        if(reg[i] == '\0'){
            i = 0;
            while (reg[i] != '\0') {
                address = 10 * address + (reg[i] - '0');
                i++;
            }
        }
        else{
            std::string pp;
            auto it = std::find(my_label.begin(), my_label.end(), reg);
            if (it != my_label.end()) {
                pp = my_pc[it - my_label.begin()];
                pp = pp.substr(1);
                int decimalNumber = std::stoi(pp, 0, 16);
                address = decimalNumber;
            } else {
                binary = "++";
                return;
            }
        }
    }

    label_reg_imme.r1 = 0;
    label_reg_imme.r2 = 0;
    label_reg_imme.r3 = 0;
    label_reg_imme.immediate = 0;
    

    Instruction_J inst;
    inst.opcode = opcode;
    inst.address = address;
    label_reg_imme.jump = deTobin(inst.address, 26);

    binary = deTobin(inst.opcode, 6) + deTobin(inst.address, 26);
}

//��ຯ��
void Assemble::assemble(const std::string& instruction, std::string& binary) {
    size_t startPos = instruction.find_first_not_of(" \t");
    std::string instruction1;
    if (startPos != std::string::npos) {
        instruction1 = instruction.substr(startPos);
    }

    label_reg_imme.label = "0";

    size_t j = instruction1.find(':');
    if(j != std::string::npos){
        std::string label;
        label = instruction1.substr(0, j);
        size_t endPos = label.find_last_not_of(" \t");
        if (endPos != std::string::npos) {
            label = label.substr(0, endPos + 1);
        }
        j = label.find(' ');
        if(j != std::string::npos){
            binary = "++";
            return;
        }
        label_reg_imme.label = label;
        my_label.push_back(label);
        my_pc.push_back(R.PC);
        instruction1 = instruction1.substr(j+1);
        startPos = instruction1.find_first_not_of(" \t");
        if (startPos != std::string::npos) {
            instruction1 = instruction1.substr(startPos);
        }
    }


    size_t i = instruction1.find(' ');
    if (i >= 5 || i == std::string::npos)
    {
        binary = "++";
        return;
    }
    std::string operator_str = instruction1.substr(0, i);
    i++;

    std::string instruction_part = instruction1.substr(i);

    if (is_R(operator_str)) {
        label_reg_imme.op = operator_str;
        ass_R(instruction_part, operator_str, binary);
    }
    else if (is_I(operator_str)) {
        label_reg_imme.op = operator_str;
        ass_I(instruction_part, operator_str, binary);
    }
    else if (is_J(operator_str)) {
        label_reg_imme.op = operator_str;
        ass_J(instruction_part, operator_str, binary);
    }
    else {
        binary = "++";
        return;
    }
}

//�ӿں���������MIPS�����ػ������string�����ַ���
std::string Assemble::interface_ass(char str[])
{
    std::string instruction(str);
    std::string binary;
    assemble(instruction, binary);
    return binary;
}

// int main() {
//     //���
//     std::string instruction, binary;
//     std::getline(std::cin, instruction);
//     assemble(instruction, binary);
//     std::cout << binary;
//     //�����

//     return 0;
// }
