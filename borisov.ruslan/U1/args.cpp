#include "args.hpp"
#include <cstring>

namespace
{
  const char IN_PREFIX[] = "in:";
  const char OUT_PREFIX[] = "out:";
  const int MAX_ARGC = 3;
}

borisov::Args borisov::parseArgs(const int argc, char **argv)
{
  borisov::Args result{"", "", false, false, true};
  if (argc > MAX_ARGC)
  {
    result.valid_ = false;
    return result;
  }
  for (int i = 1; i < argc; ++i)
  {
    const char * const arg = argv[i];
    if (std::strncmp(arg, IN_PREFIX, sizeof(IN_PREFIX) - 1) == 0)
    {
      if (result.inSet_)
      {
        result.valid_ = false;
        return result;
      }
      result.inFile_ = arg + (sizeof(IN_PREFIX) - 1);
      result.inSet_ = true;
    }
    else if (std::strncmp(arg, OUT_PREFIX, sizeof(OUT_PREFIX) - 1) == 0)
    {
      if (result.outSet_)
      {
        result.valid_ = false;
        return result;
      }
      result.outFile_ = arg + (sizeof(OUT_PREFIX) - 1);
      result.outSet_ = true;
    }
    else
    {
      result.valid_ = false;
      return result;
    }
  }
  return result;
}
