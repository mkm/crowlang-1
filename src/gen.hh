#ifndef _GEN_H_
#define _GEN_H_

#include <string>

std::string mangle(std::string);

std::string anon();
std::string constant(int);

std::string op_globl(std::string);
std::string op_label(std::string);
std::string op_move_imm(std::string, int);

#endif
