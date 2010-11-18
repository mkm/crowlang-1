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
  int value() const;
  virtual std::string toString() const;
};

class IdentifierToken : public Token {
private:
  std::string _value;

public:
  IdentifierToken(std::string);
  std::string value() const;
  virtual std::string toString() const;
};

class StringToken : public Token {
private:
  std::string _value;

public:
  StringToken(std::string);
  std::string value() const;
  virtual std::string toString() const;
};

class OpenParenToken : public Token {
public:
  OpenParenToken();
  virtual std::string toString() const;
};


class CloseParenToken : public Token {
public:
  CloseParenToken();
  virtual std::string toString() const;
};

class CommaToken : public Token {
public:
  CommaToken();
  virtual std::string toString() const;
};

#endif
