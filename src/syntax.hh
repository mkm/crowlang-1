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

class LetExpr : public Expr {
public:
  virtual std::string toString() const;
};

class IntConstantExpr : public Expr {
private:
  int _value;
  
public:
  IntConstantExpr(int);
  virtual std::string toString() const;
};

#endif
