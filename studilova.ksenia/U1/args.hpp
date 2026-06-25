#ifndef ARGS_HPP
#define ARGS_HPP

#include <string>

namespace studilova
{
  struct Args
  {
    std::string inputFile_;
    std::string outputFile_;
    bool hasInput_;
    bool hasOutput_;
    bool valid_;
  };

  Args parseArgs(int argc, char *argv[]);
}

#endif
