#ifndef _LEX_H_
#define _LEX_H_

#include <vector>
#include <string>
#include "token.hh"

std::vector<Token*> lex(std::string);

bool isNumeric(char);
bool isAlpha(char);
bool isAlphaNumeric(char);

class Lexer {
private:
  size_t _index;
  std::string& _input;
  std::vector<Token*> _tokens;

  char current();
  void next();
  bool eos();
  bool lexToken();
  void lexNumber();
  void lexWord();
  void addToken(Token*);
  
public:
  Lexer(std::string&);
  std::vector<Token*> lex();
};

class LexException {
public:
  virtual std::string message() = 0;
};

class EOSException : public LexException {
public:
  virtual std::string message();
};

class BadCharException : public LexException {
private:
  char _c;

public:
  BadCharException(char);
  virtual std::string message();
};

#endif
