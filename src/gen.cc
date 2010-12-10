#include "gen.hh"
#include <sstream>

using namespace std;

int anonCount = 0;

string mangle(string name) {
  return "__crow_" + name;
}

string anon() {
  stringstream ss("ref");
  ss << anonCount++;
  return ss.str();
}

string op_globl(string name) {
  return ".globl " + name;
}

string op_label(string name) {
  return name + ":";
}


