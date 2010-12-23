#ifndef _GEN_H_
#define _GEN_H_

#include <string>
#include <map>
#include <vector>

class SymbolTable {
private:
  std::map<std::string, int> _symbols;
  int _varCount;

public:
  SymbolTable();
  SymbolTable(std::vector<std::string>&);

  std::string pos(std::string);
  int stackSpace();
};

enum Register {
  EAX,
  EBX,
  ECX,
  EDX,
  EDI,
  ESI,
  EBP,
  ESP
};

std::string mangle(std::string);

std::string anon();
std::string constant(int);

std::string regName(Register);

void opgen(std::vector<std::string>&, std::string);
void opgen(std::vector<std::string>&, std::string, std::string);
void opgen(std::vector<std::string>&, std::string, std::string, std::string);

void loadVar(std::vector<std::string>&, Register, std::string, SymbolTable&);
void saveVar(std::vector<std::string>&, std::string, Register, SymbolTable&);

void op_globl(std::vector<std::string>&, std::string);
void op_label(std::vector<std::string>&, std::string);

void op_move_imm(std::vector<std::string>&, std::string, int, SymbolTable&);
void op_test(std::vector<std::string>&, std::string, std::string, SymbolTable&);
void op_jmp(std::vector<std::string>&, std::string);
void op_je(std::vector<std::string>&, std::string);

#endif
