#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>

class Token {
private:
  size_t _line;
  size_t _column;
  
public:
  Token(size_t, size_t);
  
  virtual std::string toString() const = 0;
  size_t line();
  size_t column();
};

class IntegerToken : public Token {
private:
  int _value;

public:
  IntegerToken(int, size_t, size_t);
  int value() const;
  virtual std::string toString() const;
};

class IdentifierToken : public Token {
private:
  std::string _value;

public:
  IdentifierToken(std::string, size_t, size_t);
  std::string value() const;
  virtual std::string toString() const;
};

class StringToken : public Token {
private:
  std::string _value;

public:
  StringToken(std::string, size_t, size_t);
  std::string value() const;
  virtual std::string toString() const;
};

class OpenParenToken : public Token {
public:
  OpenParenToken(size_t, size_t);
  virtual std::string toString() const;
};


class CloseParenToken : public Token {
public:
  CloseParenToken(size_t, size_t);
  virtual std::string toString() const;
};

class CommaToken : public Token {
public:
  CommaToken(size_t, size_t);
  virtual std::string toString() const;
};

class SemiColonToken : public Token {
public:
  SemiColonToken(size_t, size_t);
  virtual std::string toString() const;
};

class LetToken : public Token {
public:
  LetToken(size_t, size_t);
  virtual std::string toString() const;
};

#endif
