#ifndef COMMAND_LINE_OPTIONS_H_INCLUDED
#define COMMAND_LINE_OPTIONS_H_INCLUDED

#include <string>

class CommandLineOptions {
public:
  CommandLineOptions();
  bool parse(int argc, char* argv[]);
  bool isValid() const;
  bool hasInputFile() const;
  bool hasDataFile() const;
  const std::string& inputFileName() const;
  const std::string& dataFileName() const;

private:
  std::string inputFileName_;
  std::string dataFileName_;
  bool hasInputFile_;
  bool hasDataFile_;
  bool valid_;
};

#endif
