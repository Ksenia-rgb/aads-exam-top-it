#ifndef COMMAND_PROCESSOR_H_INCLUDED
#define COMMAND_PROCESSOR_H_INCLUDED

#include <string>

class DataStore;

class CommandProcessor {
public:
  explicit CommandProcessor(DataStore& dataStore);
  void processCommandLine(const std::string& line);

private:
  DataStore& dataStore_;
};

#endif
