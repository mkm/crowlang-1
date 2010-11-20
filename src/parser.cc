#include "parser.hh"

using namespace std;

SourceFile* parse(vector<Token*>& tokens) {
  return Parser(tokens).parse();
}

ParserState::ParserState(vector<Token*>& tokens) :
  _tokens(tokens),
  _index(0)
{}

Token* ParserState::current() {
  eosCheck();
  return _tokens[_index];
}

void ParserState::next() {
  _index++;
}

bool ParserState::eos() {
  return _index >= _tokens.size();
}

void ParserState::eosCheck() {
  if (eos()) {
    throw EOTException();
  }
}

ParserState& ParserState::operator=(const ParserState& other) {
  _tokens = other._tokens;
  _index = other._index;
  return *this;
}

TrState::TrState(ParserState& state) :
  _active(true),
  _current(state),
  _saved(state)
{}

TrState::TrState(TrState&& other) :
  _active(true),
  _current(other._current),
  _saved(other._saved)
{
  other._active = false;
}

TrState::~TrState() {
  if (_active) {
    _current = _saved;
  }
}

void TrState::commit() {
  _saved = _current;
}

Parser::Parser(vector<Token*>& tokens) :
  _state(tokens)
{}

SourceFile* Parser::parse() {
  return new SourceFile();
}

Token* Parser::current() {
  return _state.current();
}

void Parser::next() {
  _state.next();
}

bool Parser::eos() {
  return _state.eos();
}

void Parser::eosCheck() {
  _state.eosCheck();
}

