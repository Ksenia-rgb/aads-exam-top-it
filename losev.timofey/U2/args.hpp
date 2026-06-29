#ifndef LOSEV_ARGS_HPP
#define LOSEV_ARGS_HPP

#include <string>

namespace losev
{
  struct Args
  {
    std::string inFile;
    std::string dataFile;
    bool hasIn;
    bool hasData;
  };
  Args parseArgs(int argc, char* argv[]);
}

#endif
