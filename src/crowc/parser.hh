#ifndef _PARSER_H_
#define _PARSER_H_

#include "token.hh"
#include "syntax.hh"
#include <vector>

SourceFile* parse(std::vector<Token*>&);

class ParserState {
private:
  std::vector<Token*>& _tokens;
  size_t _index;

public:
  ParserState(std::vector<Token*>&);

  Token* current();
  void next();
  bool eos();
  void eosCheck();
  ParserState& operator=(const ParserState&);
};

class TrState {
private:
  bool _active;
  ParserState& _current;
  ParserState _saved;
  TrState(const TrState&);

public:
  TrState(ParserState&);
  TrState(TrState&&);
  ~TrState();
  void commit();
};

class Parser {
private:
  ParserState _state;

  Token* current();
  void next();
  bool eos();
  void eosCheck();

  SourceFile* parseSourceFile();
  FuncDecl* parseFuncDecl();
  Expr* parseExpr();
  Expr* parseTermExpr();
  CallExpr* parseCallExpr();
  LetExpr* parseLetExpr();
  CondExpr* parseCondExpr();
  IdentExpr* parseIdentExpr();
  IntConstantExpr* parseIntConstantExpr();
  template<class T>
  void parseToken();
  template<class T>
  std::vector<T> parseList(T (Parser::*)());
  
public:
  Parser(std::vector<Token*>&);
  SourceFile* parse();
};

class ParseException {
public:
  virtual std::string message() const = 0;
};

class EOTException : public ParseException {
public:
  virtual std::string message() const;
};

class ExpectedTokenException : public ParseException {
public:
  virtual std::string message() const;
};

template<class T>
void Parser::parseToken() {
  TrState tr(_state);
  if (!dynamic_cast<T*>(current())) {
    throw ExpectedTokenException();
  }
  next();
  tr.commit();
}

template<class T>
std::vector<T> Parser::parseList(T (Parser::*p)()) {
  TrState tr(_state);
  std::vector<T> list;
  try {
    list.push_back((this->*p)());
    while (true) {
      try {
        TrState ttr(_state);
        parseToken<CommaToken>();
        list.push_back((this->*p)());
        ttr.commit();
      } catch (ParseException& e) {
        break;
      }
    }
  } catch (ParseException& e) {
    
  }
  tr.commit();
  return list;
}

#endif
