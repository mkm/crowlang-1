#ifndef _SYNTAX_H_
#define _SYNTAX_H_

#include <string>
#include <vector>
#include "atree.hh"

class Syntax {
public:
  virtual std::string toString() const = 0;
  virtual ATree* atree() const = 0;
};

class Expr : public Syntax {
public:
  virtual void gen(std::vector<std::string>&, std::string) = 0;
};

class IdentExpr : public Expr {
private:
  std::string _name;
  
public:
  IdentExpr(std::string);
  virtual std::string toString() const;
  virtual ATree* atree() const;
  virtual void gen(std::vector<std::string>&, std::string);
  std::string name();
};

class LetExpr : public Expr {
private:
  IdentExpr* _ident;
  Expr* _value;
  Expr* _body;
  
public:
  LetExpr(IdentExpr*, Expr*, Expr*);
  virtual std::string toString() const;
  virtual ATree* atree() const;
  virtual void gen(std::vector<std::string>&, std::string);
  IdentExpr* ident();
  Expr* value();
  Expr* body();
};

class CondExpr : public Expr {
private:
  Expr* _test;
  Expr* _tBranch;
  Expr* _fBranch;

public:
  CondExpr(Expr*, Expr*, Expr*);
  virtual std::string toString() const;
  virtual ATree* atree() const;
  virtual void gen(std::vector<std::string>&, std::string);
  Expr* test();
  Expr* tBranch();
  Expr* fBranch();
};

class IntConstantExpr : public Expr {
private:
  int _value;
  
public:
  IntConstantExpr(int);
  virtual std::string toString() const;
  virtual ATree* atree() const;
  virtual void gen(std::vector<std::string>&, std::string);
  int value();
};

class CallExpr : public Expr {
private:
  IdentExpr* _func;
  std::vector<Expr*> _args;

public:
  CallExpr(IdentExpr*, std::vector<Expr*>);
  virtual std::string toString() const;
  virtual ATree* atree() const;
  virtual void gen(std::vector<std::string>&, std::string);
  IdentExpr* func();
  std::vector<Expr*> args();
};

class FuncDecl : public Syntax {
private:
  std::string _name;
  std::vector<IdentExpr*> _params;
  Expr* _body;
  
public:
  FuncDecl(std::string, std::vector<IdentExpr*>, Expr*);
  virtual std::string toString() const;
  virtual ATree* atree() const;
  virtual void gen(std::vector<std::string>&);
  std::string name();
  std::vector<IdentExpr*> params();
  Expr* body();
};

class SourceFile : public Syntax {
private:
  std::vector<FuncDecl*> _decls;
  
public:
  SourceFile(std::vector<FuncDecl*>);
  virtual std::string toString() const;
  virtual ATree* atree() const;
  virtual void gen(std::vector<std::string>&);
  std::vector<FuncDecl*> decls();
};

#endif
