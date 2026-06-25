#include "options.hpp"

#include <string>

namespace muraviev
{
  bool parseProgramOptions(const size_t argc, char** argv,
      ProgramOptions& options)
  {
    options.hasInput = false;
    options.hasOutput = false;
    if (argc < 1 || argc > 3)
    {
      return false;
    }
    for (size_t index = 1; index < argc; ++index)
    {
      const std::string argument = argv[index];
      if (argument.compare(0, 3, "in:") == 0)
      {
        if (options.hasInput)
        {
          return false;
        }
        options.hasInput = true;
        options.inputName = argument.substr(3);
      }
      else if (argument.compare(0, 4, "out:") == 0)
      {
        if (options.hasOutput)
        {
          return false;
        }
        options.hasOutput = true;
        options.outputName = argument.substr(4);
      }
      else
      {
        return false;
      }
    }
    return true;
  }
}
