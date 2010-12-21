#ifndef _GEN_H_
#define _GEN_H_

#include <string>
#include <map>
#include <vector>

class SymbolTable {
private:
  std::map<std::string, int> _symbols;
  int _lastVar;

public:
  SymbolTable();
  SymbolTable(std::vector<std::string>&);

  std::string pos(std::string);
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

std::string op_globl(std::string);
std::string op_label(std::string);

void op_move_imm(std::vector<std::string>&, std::string, int, SymbolTable&);

#endif
