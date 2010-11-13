#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>

class Token {
public:
  virtual std::string toString() const = 0;
};

class IntegerToken : public Token {
private:
  int _value;

public:
  IntegerToken(int);
  int value();
  virtual std::string toString() const;
};

#endif
