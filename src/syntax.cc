#include "syntax.hh"

using namespace std;

FuncDecl::FuncDecl(string name) :
  _name(name)
{}

string FuncDecl::toString() const {
  return "FuncDecl";
}

SourceFile::SourceFile(vector<FuncDecl*> decls) :
  _decls(decls)
{}

string SourceFile::toString() const {
  return "SourceFile";
}

LetExpr::LetExpr(IdentExpr* ident, Expr* body) :
  _ident(ident),
  _body(body)
{}

string LetExpr::toString() const {
  return "LetExpr";
}

IntConstantExpr::IntConstantExpr(int value) :
  _value(value)
{}

string IntConstantExpr::toString() const {
  return "IntConstantExpr";
}

IdentExpr::IdentExpr(string name) :
  _name(name)
{}

string IdentExpr::toString() const {
  return "IdentExpr";
}

