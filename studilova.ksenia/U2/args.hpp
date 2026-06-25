#ifndef ARGS_HPP
#define ARGS_HPP

#include <string>

namespace studilova
{
  struct Args
  {
    std::string inputFile_;
    std::string dataFile_;
    bool hasInput_;
    bool hasData_;
    bool valid_;
  };

  Args parseArgs(int argc, char *argv[]);
}

#endif
