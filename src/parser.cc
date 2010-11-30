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
  return parseSourceFile();
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

SourceFile* Parser::parseSourceFile() {
  TrState tr(_state);
  vector<FuncDecl*> decls;
  while (!eos()) {
    decls.push_back(parseFuncDecl());
  }
  tr.commit();
  return new SourceFile(decls);
}

FuncDecl* Parser::parseFuncDecl() {
  TrState tr(_state);
  IdentifierToken* nameToken = dynamic_cast<IdentifierToken*>(current());
  if (!nameToken) {
    throw ExpectedTokenException();
  }
  next();
  parseToken<OpenParenToken>();
  parseToken<CloseParenToken>();
  parseTermExpr();
  tr.commit();
  return new FuncDecl(nameToken->value());
}

Expr* Parser::parseExpr() {
  TrState tr(_state);
  Expr* expr = NULL;
  try {
    expr = parseLetExpr();
  } catch (ParseException& e) {
    expr = parseIntConstantExpr();
  }
  tr.commit();
  return expr;
}

Expr* Parser::parseTermExpr() {
  TrState tr(_state);
  Expr* expr = parseExpr();
  parseToken<SemiColonToken>();
  tr.commit();
  return expr;
}

LetExpr* Parser::parseLetExpr() {
  TrState tr(_state);
  parseToken<LetToken>();
  IdentExpr* ident = parseIdentExpr();
  Expr* expr = parseExpr();
  tr.commit();
  return new LetExpr(ident, expr);
}

IdentExpr* Parser::parseIdentExpr() {
  TrState tr(_state);
  IdentifierToken* token = dynamic_cast<IdentifierToken*>(current());
  if (!token) {
    throw ExpectedTokenException();
  }
  next();
  tr.commit();
  return new IdentExpr(token->value());
}

IntConstantExpr* Parser::parseIntConstantExpr() {
  TrState tr(_state);
  IntegerToken* token = dynamic_cast<IntegerToken*>(current());
  if (!token) {
    throw ExpectedTokenException();
  }
  next();
  tr.commit();
  return new IntConstantExpr(token->value());
}

string EOTException::message() const {
  return "Unexpected end of tokens";
}

string ExpectedTokenException::message() const {
  return "Expected a token, but did not get it";
}
