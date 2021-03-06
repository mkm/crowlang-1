#include "gen.hh"
#include <sstream>

using namespace std;

SymbolTable::SymbolTable() :
  _varCount(0)
{}

SymbolTable::SymbolTable(vector<string>& params) :
  _varCount(0)
{
  int argCount = 0;
  vector<string>::const_iterator i, n;
  for (i = params.begin(), n = params.end(); i != n; i++) {
    argCount += 1;
    _symbols[*i] = (argCount + 1) * 4;
  }
}

string SymbolTable::pos(string var) {
  if (_symbols.find(var) == _symbols.end()) {
    _varCount += 1;
    _symbols[var] = _varCount * -4;
  }
  stringstream ss;
  ss << _symbols[var] << "(" << regName(EBP) << ")";
  return ss.str();
}

int SymbolTable::stackSpace() {
  return _varCount * 4;
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

void opgen(vector<string>& ins, string opName) {
  ins.push_back(opName);
}

void opgen(vector<string>& ins, string opName, string arg) {
  ins.push_back(opName + " " + arg);
}

void opgen(vector<string>& ins, string opName, string dest, string src) {
  ins.push_back(opName + " " + src + "," + dest);
}

void loadVar(vector<string>& ins, Register dest, string src, SymbolTable& sym) {
  opgen(ins, "movl", regName(dest), sym.pos(src));
}

void saveVar(vector<string>& ins, string dest, Register src, SymbolTable& sym) {
  opgen(ins, "movl", sym.pos(dest), regName(src));
}

void op_globl(vector<string>& ins, string name) {
  ins.push_back(".globl " + name);
}

void op_label(vector<string>& ins, string name) {
  ins.push_back(name + ":");
}

void op_move_imm(vector<string>& ins, string dest, int src, SymbolTable& sym) {
  opgen(ins, "movl", regName(EAX), constant(src));
  saveVar(ins, dest, EAX, sym);
}

void op_cmp(vector<string>& ins, string dest, string src, SymbolTable& sym) {
  loadVar(ins, EAX, dest, sym);
  loadVar(ins, EBX, src, sym);
  opgen(ins, "cmpl", regName(EAX), regName(EBX));
}

void op_jmp(vector<string>& ins, string dest) {
  opgen(ins, "jmp", dest);
}

void op_je(vector<string>& ins, string dest) {
  opgen(ins, "je", dest);
}

void op_call(vector<string>& ins, string dest) {
  opgen(ins, "call", dest);
}

void op_push(vector<string>& ins, string dest, SymbolTable& sym) {
  loadVar(ins, EAX, dest, sym);
  opgen(ins, "pushl", regName(EAX));
}



