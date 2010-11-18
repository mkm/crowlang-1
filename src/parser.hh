#ifndef _PARSER_H_
#define _PARSER_H_

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
};

class TrState {
private:
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
  TrState&& tr();
  
public:
  Parser(std::vector<Token*>&);
  SourceFile* parse();
};

#endif
