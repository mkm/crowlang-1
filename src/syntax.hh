#ifndef _SYNTAX_H_
#define _SYNTAX_H_

#include <string>

class Syntax {
public:
  virtual std::string toString() const = 0;
};

class FuncDecl : public Syntax {
  virtual std::string toString() const;
};

class SourceFile : public Syntax {
  virtual std::string toString() const;
};

#endif
