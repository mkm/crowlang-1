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
  return new ATree("LetExpr");
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

IdentExpr::IdentExpr(string name) :
  _name(name)
{}

string IdentExpr::toString() const {
  return "IdentExpr";
}

ATree* IdentExpr::atree() const {
  return new ATree("IdentExpr [" + _name + "]");
}

CallExpr::CallExpr(IdentExpr* func, vector<Expr*> args) :
  _func(func),
  _args(args)
{}

string CallExpr::toString() const {
  return "CallExpr";
}

ATree* CallExpr::atree() const {
  return new ATree("CallExpr");
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

SourceFile::SourceFile(vector<FuncDecl*> decls) :
  _decls(decls)
{}

string SourceFile::toString() const {
  return "SourceFile";
}

ATree* SourceFile::atree() const {
  return (new ATree("SourceFile"))->add(_decls);
}

