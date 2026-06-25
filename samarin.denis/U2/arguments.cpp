#include "arguments.hpp"

#include <string>

#include "cli.hpp"

bool samarin::parseArguments(int argc, const char * const * argv, Options & options)
{
  const std::string personsPrefix = "in:";
  const std::string dataPrefix = "data:";
  const int minArguments = 1;
  const int maxArguments = 2;
  const int count = argc - 1;
  if (count < minArguments || count > maxArguments) {
    return false;
  }
  bool hasData = false;
  for (int i = 1; i < argc; ++i) {
    const std::string argument = argv[i];
    std::string value;
    if (detail::takeOption(argument, personsPrefix, value)) {
      if (!detail::assignOnce(options.hasPersons, options.personsName, value)) {
        return false;
      }
    } else if (detail::takeOption(argument, dataPrefix, value)) {
      if (!detail::assignOnce(hasData, options.dataName, value)) {
        return false;
      }
    } else {
      return false;
    }
  }
  return hasData;
}
