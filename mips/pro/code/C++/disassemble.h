#include <iostream>
#include <string>
#include <cmath>

class Disassemble {
    static int binToDec(const std::string& binary);
    static int binToDec2(const std::string& binary);
    static void dis_R(const std::string& binary, std::string& instruction);
    static void dis_I_J(const std::string& binary, std::string& instruction);
    static void disassemble(const std::string& binary, std::string& instruction);
public:
    static std::string interface_dis(char str[]);
};