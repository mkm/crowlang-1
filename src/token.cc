#include "token.hh"
#include <sstream>

using namespace std;

IntegerToken::IntegerToken(int value) :
  _value(value)
{}

int IntegerToken::value() {
  return _value;
}

string IntegerToken::toString() const {
  stringstream ss;
  ss << "Integer [" << _value << "]";
  return ss.str();
}

