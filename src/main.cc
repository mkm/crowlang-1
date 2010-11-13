#include <iostream>
#include <string>
#include "lex.hh"

using namespace std;

int main(/*int argc, char** argv*/) {
  try {
    string input;
    char c;
    while (!cin.get(c).eof()) {
      input += char(c);
    }
    vector<Token*> tokens = lex(input);
    vector<Token*>::const_iterator i, n;
    for (i = tokens.begin(), n = tokens.end(); i != n; i++) {
      cout << (*i)->toString() << endl;
    }
  } catch (LexException& e) {
    cout << e.message() << endl;
    return 1;
  }
}
