#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <string>

namespace muraviev
{
  struct ProgramOptions
  {
    bool hasInput;
    bool hasOutput;
    std::string inputName;
    std::string outputName;
  };

  bool parseProgramOptions(int argc, char** argv, ProgramOptions& options);
}

#endif
