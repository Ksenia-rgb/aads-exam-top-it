#include "cli.hpp"

#include <string>

bool samarin::detail::takeOption(const std::string & argument, const std::string & prefix,
    std::string & value)
{
  if (argument.size() <= prefix.size() || argument.compare(0, prefix.size(), prefix) != 0) {
    return false;
  }
  value = argument.substr(prefix.size());
  return true;
}

bool samarin::detail::assignOnce(bool & flag, std::string & target, const std::string & value)
{
  if (flag) {
    return false;
  }
  flag = true;
  target = value;
  return true;
}
