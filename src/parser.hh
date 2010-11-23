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

#endif
