#include "gen.hh"
#include <sstream>

using namespace std;

int anonCount = 0;

string mangle(string name) {
  return "__crow_" + name;
}

string anon() {
  stringstream ss;
  ss << "ref" << anonCount++;
  return ss.str();
}

string constant(int n) {
  stringstream ss;
  ss << "$" << n;
  return ss.str();
}

string op_globl(string name) {
  return ".globl " + name;
}

string op_label(string name) {
  return name + ":";
}

string op_move_imm(string dest, int src) {
  return "movl " + constant(src) + ", " + dest;
}

