#include "syntax.hh"
#include "gen.hh"

using namespace std;

LetExpr::LetExpr(IdentExpr* ident, Expr* value, Expr* body) :
  _ident(ident),
  _value(value),
  _body(body)
{}

string LetExpr::toString() const {
  return "LetExpr";
}

ATree* LetExpr::atree() const {
  return (new ATree("LetExpr"))->add(_ident->atree())->add(_value->atree())->add(_body->atree());
}

void LetExpr::gen(vector<string>& ins, string dest, SymbolTable& sym) {
  string name = _ident->name();
  _value->gen(ins, name, sym);
  _body->gen(ins, dest, sym);
}

CondExpr::CondExpr(Expr* test, Expr* tBranch, Expr* fBranch) :
  _test(test),
  _tBranch(tBranch),
  _fBranch(fBranch)
{}

string CondExpr::toString() const {
  return "CondExpr";
}

ATree* CondExpr::atree() const {
  return (new ATree("CondExpr"))->add(_test->atree())->add(_tBranch->atree())->add(_fBranch->atree());
}

void CondExpr::gen(vector<string>& ins, string dest, SymbolTable& sym) {
  string idTest = anon();
  string idZero = anon();
  string labelElse = anon();
  string labelEnd = anon();
  _test->gen(ins, idTest, sym);
  op_move_imm(ins, idZero, 0, sym);
  op_cmp(ins, idTest, idZero, sym);
  op_je(ins, labelElse);
  _tBranch->gen(ins, dest, sym);
  op_jmp(ins, labelEnd);
  op_label(ins, labelElse);
  _fBranch->gen(ins, dest, sym);
  op_label(ins, labelEnd);
}

IntConstantExpr::IntConstantExpr(int value) :
  _value(value)
{}

string IntConstantExpr::toString() const {
  return "IntConstantExpr";
}

ATree* IntConstantExpr::atree() const {
  return new ATree("IntConstantExpr");
}

void IntConstantExpr::gen(vector<string>& ins, string dest, SymbolTable& sym) {
  op_move_imm(ins, dest, _value, sym);
}

int IntConstantExpr::value() {
  return _value;
}

IdentExpr::IdentExpr(string name) :
  _name(name)
{}

string IdentExpr::toString() const {
  return "IdentExpr";
}

ATree* IdentExpr::atree() const {
  return new ATree("IdentExpr [" + _name + "]");
}

void IdentExpr::gen(vector<string>& ins, string dest, SymbolTable& sym) {
  loadVar(ins, EAX, _name, sym);
  saveVar(ins, dest, EAX, sym);
}

string IdentExpr::name() {
  return _name;
}

CallExpr::CallExpr(IdentExpr* func, vector<Expr*> args) :
  _func(func),
  _args(args)
{}

string CallExpr::toString() const {
  return "CallExpr";
}

ATree* CallExpr::atree() const {
  ATree* f = (new ATree("CallFunc"))->add(_func->atree());
  ATree* p = (new ATree("CallArgs"))->add(_args);
  return (new ATree("CallExpr"))->add(f)->add(p);
}

void CallExpr::gen(vector<string>& ins, string dest, SymbolTable& sym) {
  (void)ins;
  (void)dest;
  (void)sym;
}

IdentExpr* CallExpr::func() {
  return _func;
}

vector<Expr*> CallExpr::args() {
  return _args;
}

FuncDecl::FuncDecl(string name, vector<IdentExpr*> params, Expr* body) :
  _name(name),
  _params(params),
  _body(body)
{}

string FuncDecl::toString() const {
  return "FuncDecl";
}

ATree* FuncDecl::atree() const {
  ATree* p = (new ATree("FuncParams"))->add(_params);
  ATree* b = (new ATree("FuncBody"))->add(_body->atree());
  return (new ATree("FuncDecl [" + _name + "]"))->add(p)->add(b);
}

void FuncDecl::gen(vector<string>& ins) {
  SymbolTable sym;
  op_globl(ins, mangle(_name));
  op_label(ins, mangle(_name));
  opgen(ins, "pushl", regName(EBP));
  opgen(ins, "movl", regName(EBP), regName(ESP));

  vector<string> insRest;
  string rv = anon();
  _body->gen(insRest, rv, sym);
  loadVar(insRest, EAX, rv, sym);
  opgen(insRest, "movl", regName(ESP), regName(EBP));
  opgen(insRest, "popl", regName(EBP));
  opgen(insRest, "ret");

  opgen(ins, "subl", regName(ESP), constant(sym.stackSpace()));
  ins.insert(ins.end(), insRest.begin(), insRest.end());
}

string FuncDecl::name() {
  return _name;
}

std::vector<IdentExpr*> FuncDecl::params() {
  return _params;
}

Expr* FuncDecl::body() {
  return _body;
}

SourceFile::SourceFile(vector<FuncDecl*> decls) :
  _decls(decls)
{}

string SourceFile::toString() const {
  return "SourceFile";
}

ATree* SourceFile::atree() const {
  return (new ATree("SourceFile"))->add(_decls);
}

void SourceFile::gen(vector<string>& ins) {
  vector<FuncDecl*>::const_iterator i, n;
  for (i = _decls.begin(), n = _decls.end(); i != n; i++) {
    (*i)->gen(ins);
  }
}

vector<FuncDecl*> SourceFile::decls() {
  return _decls;
}

