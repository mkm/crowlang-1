#include "args.hh"

using namespace std;

Config::Config(int argc, char** argv) :
  _sourceFile(),
  _quiet(false),
  _goal(Compile),
  _dumpParse(false)
{
  parseArgs(convertArgs(argc, argv));
}

vector<string> Config::convertArgs(int argc, char** argv) {
  vector<string> args;
  for (int i = 1; i < argc; i++) {
    args.push_back(argv[i]);
  }
  return args;
}

void Config::parseArgs(vector<string> args) {
  vector<string>::const_iterator i, n;
  for (i = args.begin(), n = args.end(); i != n; i++) {
    if (*i == "--lex") {
      _goal = Lex;
    } else if (*i == "--parse") {
      _goal = Parse;
    } else if (*i == "--quiet") {
      _quiet = true;
    } else if (*i == "--dump-parse") {
      _dumpParse = true;
    } else {
      if (_sourceFile == "") {
        _sourceFile = *i;
      } else {
        throw MultipleFileException();
      }
    }
  }
  if (_sourceFile == "") {
    throw NoFileException();
  }
}

string Config::sourceFile() {
  return _sourceFile;
}

bool Config::quiet() {
  return _quiet;
}

Goal Config::goal() {
  return _goal;
}

bool Config::dumpParse() {
  return _dumpParse;
}

string MultipleFileException::message() const {
  return "Too many input files";
}

string NoFileException::message() const {
  return "No input file.";
}

string NoSuchFileException::message() const {
  return "Input file does not exist";
}
