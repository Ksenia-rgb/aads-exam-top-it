#include "args.hpp"
#include <stdexcept>

namespace losev
{
  Args parseArgs(int argc, char* argv[])
  {
    Args result;
    result.hasIn = false;
    result.hasData = false;
    for (int i = 1; i < argc; ++i)
    {
      std::string arg = argv[i];
      if (arg.substr(0, 3) == "in:")
      {
        if (result.hasIn)
        {
          throw std::invalid_argument("Duplicate in: argument");
        }
        result.inFile = arg.substr(3);
        result.hasIn = true;
      }
      else if (arg.substr(0, 5) == "data:")
      {
        if (result.hasData)
        {
          throw std::invalid_argument("Duplicate data: argument");
        }
        result.dataFile = arg.substr(5);
        result.hasData = true;
      }
      else
      {
        throw std::invalid_argument("Invalid argument: " + arg);
      }
    }

    if (!result.hasData)
    {
      throw std::invalid_argument("data: argument is required");
    }

    return result;
  }
}
