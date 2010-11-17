#include "token.hh"
#include <sstream>

using namespace std;

IntegerToken::IntegerToken(int value) :
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

IdentifierToken::IdentifierToken(string value) :
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

StringToken::StringToken(string value) :
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

OpenParenToken::OpenParenToken()
{}

string OpenParenToken::toString() const {
  return "OpenParen";
}

CloseParenToken::CloseParenToken()
{}

string CloseParenToken::toString() const {
  return "CloseParen";
}

