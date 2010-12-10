#include "op.hh"

using namespace std;

string mangle(string name) {
  return "__crow_" + name;
}

string op_globl(string name) {
  return ".globl " + name;
}

string op_label(string name) {
  return name + ":";
}


