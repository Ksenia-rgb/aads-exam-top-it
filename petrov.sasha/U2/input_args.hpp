#ifndef INPUT_ARGS_HPP
#define INPUT_ARGS_HPP

#include <string>

namespace petrov
{
  struct ProgramOptions
  {
    std::string personsFile;
    std::string dataFile;
    bool hasPersonsFile;
  };

  bool parseArguments(int argc, char* argv[], ProgramOptions& options);
}

#endif
