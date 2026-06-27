#include "arguments.hpp"

#include <string>

#include "cli.hpp"

bool samarin::parseArguments(int argc, const char * const * argv, Options & options)
{
  const std::string inputPrefix = "in:";
  const std::string outputPrefix = "out:";
  const int maxArguments = 2;
  if (argc - 1 > maxArguments) {
    return false;
  }
  for (int i = 1; i < argc; ++i) {
    const std::string argument = argv[i];
    std::string value;
    if (detail::takeOption(argument, inputPrefix, value)) {
      if (!detail::assignOnce(options.hasInput, options.inputName, value)) {
        return false;
      }
    } else if (detail::takeOption(argument, outputPrefix, value)) {
      if (!detail::assignOnce(options.hasOutput, options.outputName, value)) {
        return false;
      }
    } else {
      return false;
    }
  }
  return true;
}
