#include "args.hpp"
#include <string>

namespace burukov
{

  bool startsWith(const std::string& arg, const std::string& prefix)
  {
    if (arg.size() < prefix.size())
    {
      return false;
    }
    return arg.compare(0, prefix.size(), prefix) == 0;
  }

  Args parseArgs(int argc, char** argv)
  {
    Args res{"", "", false, false, true};
    const std::string inPrefix = "in:";
    const std::string outPrefix = "out:";
    if (argc - 1 > 2)
    {
      res.valid = false;
      return res;
    }
    for (int i = 1; i < argc; ++i)
    {
      std::string arg(argv[i]);
      if (startsWith(arg, inPrefix))
      {
        if (res.hasIn)
        {
          res.valid = false;
          return res;
        }
        res.inFile = arg.substr(inPrefix.size());
        res.hasIn = true;
      }
      else if (startsWith(arg, outPrefix))
      {
        if (res.hasOut)
        {
          res.valid = false;
          return res;
        }
        res.outFile = arg.substr(outPrefix.size());
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

  DataArgs parseDataArgs(int argc, char** argv)
  {
    DataArgs res{"", "", false, false, true};
    const std::string inPrefix = "in:";
    const std::string dataPrefix = "data:";
    if (argc < 2 || argc - 1 > 2)
    {
      res.valid = false;
      return res;
    }
    for (int i = 1; i < argc; ++i)
    {
      std::string arg(argv[i]);
      if (startsWith(arg, inPrefix))
      {
        if (res.hasIn)
        {
          res.valid = false;
          return res;
        }
        res.inFile = arg.substr(inPrefix.size());
        res.hasIn = true;
      }
      else if (startsWith(arg, dataPrefix))
      {
        if (res.hasData)
        {
          res.valid = false;
          return res;
        }
        res.dataFile = arg.substr(dataPrefix.size());
        res.hasData = true;
      }
      else
      {
        res.valid = false;
        return res;
      }
    }
    if (!res.hasData)
    {
      res.valid = false;
    }
    return res;
  }

}
