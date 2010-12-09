#include "syntax.hh"

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



IntConstantExpr::IntConstantExpr(int value) :
  _value(value)
{}

string IntConstantExpr::toString() const {
  return "IntConstantExpr";
}

ATree* IntConstantExpr::atree() const {
  return new ATree("IntConstantExpr");
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

vector<FuncDecl*> SourceFile::decls() {
  return _decls;
}

