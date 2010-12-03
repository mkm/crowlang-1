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
  
};

class IdentExpr : public Expr {
private:
  std::string _name;
  
public:
  IdentExpr(std::string);
  virtual std::string toString() const;
  virtual ATree* atree() const;
};

class LetExpr : public Expr {
  IdentExpr* _ident;
  Expr* _value;
  Expr* _body;
  
public:
  LetExpr(IdentExpr*, Expr*, Expr*);
  virtual std::string toString() const;
  virtual ATree* atree() const;
};

class IntConstantExpr : public Expr {
private:
  int _value;
  
public:
  IntConstantExpr(int);
  virtual std::string toString() const;
  virtual ATree* atree() const;
};

class CallExpr : public Expr {
private:
  IdentExpr* _func;
  std::vector<Expr*> _args;

public:
  CallExpr(IdentExpr*, std::vector<Expr*>);
  virtual std::string toString() const;
  virtual ATree* atree() const;
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
};

class SourceFile : public Syntax {
private:
  std::vector<FuncDecl*> _decls;
  
public:
  SourceFile(std::vector<FuncDecl*>);
  virtual std::string toString() const;
  virtual ATree* atree() const;
};

#endif
