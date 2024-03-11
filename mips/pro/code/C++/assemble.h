#include <iostream>
#include <string>
#include <cmath>

struct Label_Reg_Imme {
    std::string label;
    int r1;
    int r2;
    int r3;
    int immediate;
    std::string op;
    std::string jump;
};

class Assemble {
    static bool is_R(const std::string& operator_str);
    static bool is_I(const std::string& operator_str);
    static bool is_J(const std::string& operator_str);
    static std::string deTobin(int decimal, int length);
    static void ass_R(std::string& instruction, const std::string& operator_str, std::string& binary);
    static void ass_I(std::string& instruction, const std::string& operator_str, std::string& binary);
    static void ass_J(std::string& instruction, const std::string& operator_str, std::string& binary);
    static void assemble(const std::string& instruction, std::string& binary);
    static void pc_add(int k);
public:
    static std::string interface_ass(char str[]);
    static void init_pc();
};