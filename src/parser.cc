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
  vector<IdentExpr*> params = parseList<IdentExpr*>(&Parser::parseIdentExpr);
  parseToken<CloseParenToken>();
  Expr* body = parseTermExpr();
  tr.commit();
  return new FuncDecl(nameToken->value(), params, body);
}

Expr* Parser::parseExpr() {
  TrState tr(_state);
  Expr* expr = NULL;
  try {
    expr = parseLetExpr();
  } catch (ParseException& e) {
    try {
      expr = parseIntConstantExpr();
    } catch (ParseException& e) {
      try {
        expr = parseCallExpr();
      } catch (ParseException& e) {
        try {
          expr = parseCondExpr();
        } catch (ParseException& e) {
          expr = parseIdentExpr();
        }
      }
    }
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

CallExpr* Parser::parseCallExpr() {
  TrState tr(_state);
  IdentExpr* func = parseIdentExpr();
  parseToken<OpenParenToken>();
  vector<Expr*> args = parseList<Expr*>(&Parser::parseExpr);
  parseToken<CloseParenToken>();
  tr.commit();
  return new CallExpr(func, args);
}

LetExpr* Parser::parseLetExpr() {
  TrState tr(_state);
  parseToken<LetToken>();
  IdentExpr* ident = parseIdentExpr();
  parseToken<EqualToken>();
  Expr* value = parseExpr();
  parseToken<InToken>();
  Expr* body = parseExpr();
  tr.commit();
  return new LetExpr(ident, value, body);
}

CondExpr* Parser::parseCondExpr() {
  TrState tr(_state);
  parseToken<IfToken>();
  Expr* test = parseExpr();
  parseToken<ThenToken>();
  Expr* trueBranch = parseExpr();
  parseToken<ElseToken>();
  Expr* falseBranch = parseExpr();
  tr.commit();
  return new CondExpr(test, trueBranch, falseBranch);
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
