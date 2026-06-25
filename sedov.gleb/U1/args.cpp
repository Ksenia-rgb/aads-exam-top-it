#include "args.hpp"

bool sedov::hasPrefix(const std::string & arg, const std::string & prefix)
{
  if (arg.size() < prefix.size())
  {
    return false;
  }
  return arg.compare(0, prefix.size(), prefix) == 0;
}

std::string sedov::stripPrefix(const std::string & arg, const std::string & prefix)
{
  return arg.substr(prefix.size());
}

sedov::Args sedov::parseArgs(int argc, char ** argv)
{
  Args res{"", "", false, false, true};
  if (argc - 1 > 2)
  {
    res.valid = false;
    return res;
  }
  const std::string inPrefix = "in:";
  const std::string outPrefix = "out:";
  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    if (hasPrefix(arg, inPrefix))
    {
      if (res.hasIn)
      {
        res.valid = false;
        return res;
      }
      res.inFile = stripPrefix(arg, inPrefix);
      res.hasIn = true;
    }
    else if (hasPrefix(arg, outPrefix))
    {
      if (res.hasOut)
      {
        res.valid = false;
        return res;
      }
      res.outFile = stripPrefix(arg, outPrefix);
      res.hasOut = true;
    }
    else
    {
      res.valid = false;
      return res;
    }
  }
  return res;
}
