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

string LetExpr::toString() const {
  return "LetExpr";
}

IntConstantExpr::IntConstantExpr(int value) :
  _value(value)
{}

string IntConstantExpr::toString() const {
  return "IntConstantExpr";
}

