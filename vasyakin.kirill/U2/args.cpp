#include "args.hpp"

bool vasyakin::splitArg(const std::string& arg, const std::string& key, std::string& value)
{
  if (arg.size() < key.size() || arg.compare(0, key.size(), key) != 0)
  {
    return false;
  }

  value = arg.substr(key.size());
  return !value.empty();
}
