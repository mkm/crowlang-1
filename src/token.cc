#include "token.hh"
#include <sstream>

using namespace std;

Token::Token(size_t line, size_t column) :
  _line(line),
  _column(column)
{}

IntegerToken::IntegerToken(int value, size_t line, size_t column) :
  Token(line, column),
  _value(value)
{}

int IntegerToken::value() const {
  return _value;
}

string IntegerToken::toString() const {
  stringstream ss;
  ss << "Integer [" << _value << "]";
  return ss.str();
}

IdentifierToken::IdentifierToken(string value, size_t line, size_t column) :
  Token(line, column),
  _value(value)
{}

string IdentifierToken::value() const {
  return _value;
}

string IdentifierToken::toString() const {
  stringstream ss;
  ss << "Identifier [" << _value << "]";
  return ss.str();
}

StringToken::StringToken(string value, size_t line, size_t column) :
  Token(line, column),
  _value(value)
{}

string StringToken::value() const {
  return _value;
}

string StringToken::toString() const {
  stringstream ss;
  ss << "String [" << _value << "]";
  return ss.str();
}

OpenParenToken::OpenParenToken(size_t line, size_t column) :
  Token(line, column)
{}

string OpenParenToken::toString() const {
  return "OpenParen";
}

CloseParenToken::CloseParenToken(size_t line, size_t column) :
  Token(line, column)
{}

string CloseParenToken::toString() const {
  return "CloseParen";
}

CommaToken::CommaToken(size_t line, size_t column) :
  Token(line, column)
{}

string CommaToken::toString() const {
  return "Comma";
}

SemiColonToken::SemiColonToken(size_t line, size_t column) :
  Token(line, column)
{}

string SemiColonToken::toString() const {
  return "SemiColon";
}

EqualToken::EqualToken(size_t line, size_t column) :
  Token(line, column)
{}

string EqualToken::toString() const {
  return "Equal";
}

LetToken::LetToken(size_t line, size_t column) :
  Token(line, column)
{}

string LetToken::toString() const {
  return "Let";
}

InToken::InToken(size_t line, size_t column) :
  Token(line, column)
{}

string InToken::toString() const {
  return "In";
}



