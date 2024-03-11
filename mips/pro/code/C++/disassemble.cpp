#include"disassemble.h"

 std::string registersdis[32] = {
"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
"$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
"$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"
};

int Disassemble::binToDec(const std::string& binary) {
    int length = binary.length();
    int decimal = 0;
    for (int i = 0; i < length; i++) {
        if (binary[i] == '1') {
            decimal += std::pow(2, length - 1 - i);
        }
        else if (binary[i] != '0') {
            // Handle error if the input string contains characters other than '0' and '1'
            return -1;
        }
    }
    if (decimal < 0 || decimal > 31)
        return -1;
    return decimal;
}

int Disassemble::binToDec2(const std::string& binary) {
    int length = binary.length();
    int decimal = 0;
    for (int i = 0; i < length; i++) {
        if (binary[i] == '1') {
            decimal += std::pow(2, length - 1 - i);
        }
        else if (binary[i] != '0') {
            // Handle error if the input string contains characters other than '0' and '1'
            return -1;
        }
    }
    return decimal;
}


void Disassemble::dis_R(const std::string& binary, std::string& instruction) {
    int reg;
    std::string op, reg1, reg2, reg3;

    std::string func = binary.substr(26, 6);
    if (func == "100000") {
        op = "add";
    }
    else if (func == "100010") {
        op = "sub";
    }
    else if (func == "100100") {
        op = "and";
    }
    else if (func == "100101") {
        op = "or";
    }
    else if (func == "100111") {
        op = "nor";
    }
    else if (func == "000000") {
        op = "sll";
    }
    else if (func == "000010") {
        op = "srl";
    }
    else if (func == "001000") {
        op = "jr";
    }
    else {
        instruction = "++";
        return;
    }

    if (op != "sll" && op != "srl" && op != "jr") {
        reg = binToDec(binary.substr(6, 5));
        if (reg == -1) {
            instruction = "++";
            return;
        }
        if (reg != -1) {
            reg1 = registersdis[reg];
        }
        reg = binToDec(binary.substr(11, 5));
        if (reg == -1) {
            instruction = "++";
            return;
        }
        if (reg != -1) {
            reg2 = registersdis[reg];
        }
        reg = binToDec(binary.substr(16, 5));
        if (reg == -1) {
            instruction = "++";
            return;
        }
        if (reg != -1) {
            reg3 = registersdis[reg];
        }
        instruction = op + " " + reg3 + ", " + reg1 + ", " + reg2;
    }
    else {
        if (op == "jr") {
            reg = binToDec(binary.substr(6, 5));
            if (reg == -1) {
                instruction = "++";
                return;
            }
            if (reg != -1) {
                reg1 = registersdis[reg];
            }
            instruction = op + " " + reg1;
        }
        else {
            reg = binToDec(binary.substr(11, 5));
            if (reg == -1) {
                instruction = "++";
                return;
            }
            if (reg != -1) {
                reg1 = registersdis[reg];
            }
            reg = binToDec(binary.substr(16, 5));
            if (reg == -1) {
                instruction = "++";
                return;
            }
            if (reg != -1) {
                reg2 = registersdis[reg];
            }
            reg = binToDec(binary.substr(21, 5));
            if (reg == -1) {
                instruction = "++";
                return;
            }
            if (reg != -1) {
                reg3 = std::to_string(reg);
            }
            instruction = op + " " + reg2 + ", " + reg1 + ", " + reg3;
        }
    }
}

void Disassemble::dis_I_J(const std::string& binary, std::string& instruction) {
    int reg;
    std::string op, reg1, reg2, immediate, address;

    std::string func = binary.substr(0, 6);
    if (func == "001000") {
        op = "addi";
    }
    else if (func == "001101") {
        op = "ori";
    }
    else if (func == "001111") {
        op = "lui";
    }
    else if (func == "100011") {
        op = "lw";
    }
    else if (func == "101011") {
        op = "sw";
    }
    else if (func == "000100") {
        op = "beq";
    }
    else if (func == "000101") {
        op = "bne";
    }
    else if (func == "000010") {
        op = "j";
    }
    else if (func == "000011") {
        op = "jal";
    }
    else {
        instruction = "++";
        return;
    }

    if (op == "lui") {
        reg = binToDec(binary.substr(11, 5));
        if (reg == -1) {
            instruction = "++";
            return;
        }
        if (reg != -1) {
            reg2 = registersdis[reg];
        }
        reg = binToDec2(binary.substr(16, 16));
        if (reg != -1) {
            immediate = std::to_string(reg);
        }
        instruction = op + " " + reg2 + ", " + immediate;
    }
    else if (op == "j" || op == "jal") {
        reg = binToDec2(binary.substr(6, 26));
        if (reg != -1) {
            address = std::to_string(reg);
        }
        instruction = op + " " + address;
    }
    else {
        reg = binToDec(binary.substr(6, 5));
        if (reg == -1) {
            instruction = "++";
            return;
        }
        if (reg != -1) {
            reg1 = registersdis[reg];
        }
        reg = binToDec(binary.substr(11, 5));
        if (reg == -1) {
            instruction = "++";
            return;
        }
        if (reg != -1) {
            reg2 = registersdis[reg];
        }
        reg = binToDec2(binary.substr(16, 16));
        if (reg != -1) {
            immediate = std::to_string(reg);
        }
        if (op == "lw" || op == "sw") {
            instruction = op + " " + reg2 + ", " + immediate + "(" + reg1 + ")";
        }
        else {
            instruction = op + " " + reg2 + ", " + reg1 + ", " + immediate;
        }
    }
}

void Disassemble::disassemble(const std::string& binary, std::string& instruction) {
    std::string opcode = binary.substr(0, 6);
    if (opcode == "000000") {
        dis_R(binary, instruction);
    }
    else {
        dis_I_J(binary, instruction);
    }
}

//接口函数：传入机器码，返回MIPS指令的string类型字符串
std::string Disassemble::interface_dis(char str[])
{
    std::string binary(str);
    std::string instruction;
    disassemble(binary, instruction);
    return instruction;
}

// int main() {
//     std::string binary, instruction;
//     std::getline(std::cin, binary);
//     disassemble(binary, instruction);
//     std::cout << instruction;
//     return 0;
// }
