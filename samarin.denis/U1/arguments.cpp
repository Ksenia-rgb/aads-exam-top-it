#include "arguments.hpp"

#include <string>

namespace {
  bool hasPrefix(const std::string & text, const std::string & prefix)
  {
    return text.size() >= prefix.size() && text.compare(0, prefix.size(), prefix) == 0;
  }
}

bool samarin::parseArguments(int argc, const char * const * argv, options_t & options)
{
  const std::string inputPrefix = "in:";
  const std::string outputPrefix = "out:";
  const int maxArguments = 2;
  if (argc - 1 > maxArguments) {
    return false;
  }
  for (int i = 1; i < argc; ++i) {
    const std::string argument = argv[i];
    if (hasPrefix(argument, inputPrefix)) {
      const std::string name = argument.substr(inputPrefix.size());
      if (options.hasInput || name.empty()) {
        return false;
      }
      options.hasInput = true;
      options.inputName = name;
    } else if (hasPrefix(argument, outputPrefix)) {
      const std::string name = argument.substr(outputPrefix.size());
      if (options.hasOutput || name.empty()) {
        return false;
      }
      options.hasOutput = true;
      options.outputName = name;
    } else {
      return false;
    }
  }
  return true;
}
