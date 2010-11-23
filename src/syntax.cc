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
