#include "input_args.hpp"

bool petrov::parseArguments(int argc, char* argv[], ProgramOptions& options)
{
  options.hasPersonsFile = false;
  bool hasData = false;
  if (argc < 2 || argc > 3)
  {
    return false;
  }
  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    if (arg.find("in:") == 0)
    {
      if (options.hasPersonsFile)
      {
        return false;
      }

      options.hasPersonsFile = true;
      options.personsFile = arg.substr(3);
    } else if (arg.find("data:") == 0) {
      if (hasData)
      {
        return false;
      }

      hasData = true;
      options.dataFile = arg.substr(5);
    } else {
      return false;
    }
  }
  return hasData;
}
