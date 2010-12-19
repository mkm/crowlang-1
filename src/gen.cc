#include "gen.hh"
#include <sstream>

using namespace std;

SymbolTable::SymbolTable() :
  _lastVar(-4)
{}

SymbolTable::SymbolTable(vector<string>& params) :
  _lastVar(-4)
{
  (void)params;
}

string SymbolTable::pos(string var) {
  if (_symbols.find(var) == _symbols.end()) {
    _symbols[var] = (_lastVar -= 4);
  }
  stringstream ss;
  ss << _symbols[var] << "(" << regName(EBP) << ")";
  return ss.str();
}

int anonCount = 0;

string mangle(string name) {
  return "__crow_" + name;
}

string anon() {
  stringstream ss;
  ss << "ref" << anonCount++;
  return ss.str();
}

string constant(int n) {
  stringstream ss;
  ss << "$" << n;
  return ss.str();
}

string regName(Register reg) {
  switch (reg) {
  case EAX: return "%eax";
  case EBX: return "%ebx";
  case ECX: return "%ecx";
  case EDX: return "%edx";
  case EDI: return "%edi";
  case ESI: return "%esi";
  case EBP: return "%ebp";
  case ESP: return "%esp";
  default:
    // error
    return "%invalid";
  }
}

void opgen(vector<string>& ins, string opName, string dest, string src) {
  ins.push_back(opName + " " + dest + "," + src);
}

void loadVar(vector<string>& ins, Register dest, string src, SymbolTable& sym) {
  opgen(ins, "movl", sym.pos(src), regName(dest));
}

void saveVar(vector<string>& ins, string dest, Register src, SymbolTable& sym) {
  opgen(ins, "movl", regName(src), sym.pos(dest));
}

string op_globl(string name) {
  return ".globl " + name;
}

string op_label(string name) {
  return name + ":";
}

void op_move_imm(vector<string>& ins, string dest, int src, SymbolTable& sym) {
  opgen(ins, "movl", constant(src), regName(EAX));
  saveVar(ins, dest, EAX, sym);
}

