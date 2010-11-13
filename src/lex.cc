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
  _input(input)
{}

vector<Token*> Lexer::lex() {
  while (lexToken());
  return _tokens;
}

char Lexer::current() {
  if (eos()) {
    throw EOSException();
  }
  return _input[_index];
}

void Lexer::next() {
  _index++;
}

bool Lexer::eos() {
  return _index >= _input.length();
}

bool Lexer::lexToken() {
  if (eos()) {
    return false;
  }
  char c = current();
  if (isNumeric(c)) {
    lexNumber();
  } else if (isAlpha(c)) {
    lexWord();
  } else if (isWhite(c)) {
    next();
  } else {
    throw BadCharException(c);
  }
  return true;
}

void Lexer::lexNumber() {
  string s;
  int value;
  while (!eos() && isNumeric(current())) {
    s += current();
    next();
  }
  stringstream(s) >> value;
  addToken(new IntegerToken(value));
}

void Lexer::lexWord() {
  
}

void Lexer::addToken(Token* token) {
  _tokens.push_back(token);
}

string EOSException::message() {
  return "Unexpected end of input";
}

BadCharException::BadCharException(char c) :
  _c(c)
{}

string BadCharException::message() {
  stringstream ss;
  ss << "Unexpected character '" << _c << "' (" << int(_c) << ")";
  return ss.str();
}
