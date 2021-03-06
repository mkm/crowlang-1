#include "lex.hh"
#include <sstream>

using namespace std;

vector<Token*> lex(string input) {
  return Lexer(input).lex();
}

bool isNumeric(char c) {
  return '0' <= c && c <= '9';
}

bool isAlpha(char c) {
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_';
}

bool isAlphaNumeric(char c) {
  return isNumeric(c) || isAlpha(c);
}

bool isWhite(char c) {
  return c == ' ' || c == '\n' || c == '\t';
}

Lexer::Lexer(string& input) :
  _index(0),
  _line(1),
  _column(0),
  _input(input)
{}

vector<Token*> Lexer::lex() {
  while (lexToken());
  return _tokens;
}

char Lexer::current() {
  eosCheck();
  return _input[_index];
}

void Lexer::next() {
  if (current() == '\n') {
    _line++;
    _column = 0;
  } else {
    _column++;
  }
  _index++;
}

bool Lexer::eos() {
  return _index >= _input.size();
}

void Lexer::eosCheck() {
  if (eos()) {
    throw EOSException();
  }
}

bool Lexer::lexToken() {
  if (eos()) {
    return false;
  }
  char c = current();
  switch (c) {
  case '(':
    addToken(new OpenParenToken(_line, _column));
    next();
    break;
  case ')':
    addToken(new CloseParenToken(_line, _column));
    next();
    break;
  case ',':
    addToken(new CommaToken(_line, _column));
    next();
    break;
  case ';':
    addToken(new SemiColonToken(_line, _column));
    next();
    break;
  case '=':
    addToken(new EqualToken(_line, _column));
    next();
    break;
  default:
    if (isNumeric(c)) {
      lexNumber();
    } else if (isAlpha(c)) {
      lexWord();
    } else if (c == '"') {
      lexString();
    } else if (isWhite(c)) {
      next();
    } else {
      throw BadCharException(c, _line, _column);
    }
  }
  return true;
}

void Lexer::lexNumber() {
  string s;
  char c = '\0';
  int value;
  while (!eos() && isNumeric(c = current())) {
    s += c;
    next();
  }
  if (isAlpha(c)) {
    throw BadCharException(c, _line, _column);
  }
  stringstream(s) >> value;
  addToken(new IntegerToken(value, _line, _column));
}

void Lexer::lexWord() {
  string value;
  char c;
  while (!eos() && isAlphaNumeric(c = current())) {
    value += c;
    next();
  }
  addToken(wordToToken(value, _line, _column));
}

void Lexer::lexString() {
  string value;
  char c;
  next(); // skip initial quote
  while ((c = current()) != '"') {
    value += c;
    next();
  }
  eosCheck();
  next(); // skip terminating quote
  addToken(new StringToken(value, _line, _column));
}

Token* Lexer::wordToToken(string value, size_t line, size_t column) {
  if (value == "let") {
    return new LetToken(line, column);
  } else if (value == "in") {
    return new InToken(line, column);
  } else if (value == "if") {
    return new IfToken(line, column);
  } else if (value == "then") {
    return new ThenToken(line, column);
  } else if (value == "else") {
    return new ElseToken(line, column);
  } else {
    return new IdentifierToken(value, line, column);
  }
}

void Lexer::addToken(Token* token) {
  _tokens.push_back(token);
}

LexException::LexException(size_t line, size_t column) :
  _line(line),
  _column(column)
{}

EOSException::EOSException() :
  LexException(0, 0)
{}

string EOSException::message() {
  return "Unexpected end of input";
}

BadCharException::BadCharException(char c, size_t line, size_t column) :
  LexException(line, column),
  _c(c)
{}

string BadCharException::message() {
  stringstream ss;
  ss << _line << ":" << _column << ": Unexpected character '" << _c << "' (" << int(_c) << ")";
  return ss.str();
}
