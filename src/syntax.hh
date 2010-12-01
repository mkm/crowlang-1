#ifndef _SYNTAX_H_
#define _SYNTAX_H_

#include <string>
#include <vector>

class Syntax {
public:
  virtual std::string toString() const = 0;
};

class FuncDecl : public Syntax {
private:
  std::string _name;
  
public:
  FuncDecl(std::string);
  virtual std::string toString() const;
};

class SourceFile : public Syntax {
private:
  std::vector<FuncDecl*> _decls;
  
public:
  SourceFile(std::vector<FuncDecl*>);
  virtual std::string toString() const;
};

class Expr : public Syntax {
  
};

class IdentExpr : public Expr {
private:
  std::string _name;
  
public:
  IdentExpr(std::string);
  virtual std::string toString() const;
};

class LetExpr : public Expr {
  IdentExpr* _ident;
  Expr* _value;
  Expr* _body;
  
public:
  LetExpr(IdentExpr*, Expr*, Expr*);
  virtual std::string toString() const;
};

class IntConstantExpr : public Expr {
private:
  int _value;
  
public:
  IntConstantExpr(int);
  virtual std::string toString() const;
};

class CallExpr : public Expr {
private:
  IdentExpr* _func;
  std::vector<Expr*> _args;

public:
  CallExpr(IdentExpr*, std::vector<Expr*>);
  virtual std::string toString() const;
};

#endif
