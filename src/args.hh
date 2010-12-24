#ifndef _ARGS_H_
#define _ARGS_H_

#include <vector>
#include <string>

enum Goal {
  Lex,
  Parse,
  Assemble,
  Compile
};

class Config {
private:
  std::string _sourceFile;
  bool _quiet;
  Goal _goal;
  bool _dumpParse;
  bool _dumpAssembly;
  std::string _outputFile;

  std::vector<std::string> convertArgs(int, char**);
  void parseArgs(std::vector<std::string>);

public:
  Config(int, char**);

  std::string sourceFile();
  bool quiet();
  Goal goal();
  bool dumpParse();
  bool dumpAssembly();
  std::string outputFile();
};

class ArgException {
public:
  virtual std::string message() const = 0;
};

class MultipleFileException : public ArgException {
public:
  virtual std::string message() const;
};

class NoFileException : public ArgException {
public:
  virtual std::string message() const;
};

class NoSuchFileException : public ArgException {
public:
  virtual std::string message() const;
};

#endif
