#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <cstddef>
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

  bool parseProgramOptions(size_t argc, char** argv, ProgramOptions& options);
}

#endif
