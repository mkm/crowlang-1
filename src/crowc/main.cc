#include <iostream>
#include <fstream>
#include <string>
#include "lex.hh"
#include "parser.hh"
#include "args.hh"

using namespace std;

int main(int argc, char** argv) {
  bool quiet = false;
  try {
    Config config(argc, argv);
    quiet = config.quiet();
    ifstream source(config.sourceFile().c_str());
    if (source.fail()) {
      throw NoSuchFileException();
    }
    string input;
    char c;
    while (!source.get(c).eof()) {
      input += char(c);
    }
    if (config.goal() < Lex) {
      return 0;
    }
    vector<Token*> tokens = lex(input);
    if (config.goal() < Parse) {
      return 0;
    }
    SourceFile* syntax = parse(tokens);
    if (config.dumpParse()) {
      syntax->atree()->write(&cout);
    }
    if (config.goal() < Compile) {
      return 0;
    }
    ofstream asmFile(config.outputFile());
    vector<string> assembly;
    syntax->gen(assembly);
    vector<string>::const_iterator i, n;
    for (i = assembly.begin(), n = assembly.end(); i != n; i++) {
      asmFile << *i << endl;
    }
  } catch (LexException& e) {
    if (!quiet) {
      cerr << e.message() << endl;
    }
    return 1;
  } catch (ParseException& e) {
    if (!quiet) {
      cerr << e.message() << endl;
    }
    return 2;
  } catch (ArgException& e) {
    if (!quiet) {
      cerr << e.message() << endl;
    }
    return 126;
  } catch (exception& e) {
    if (!quiet) {
      cerr << "runtime exception: " << e.what() << endl;
    }
    return 127;
  }
  return 0;
}

