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

