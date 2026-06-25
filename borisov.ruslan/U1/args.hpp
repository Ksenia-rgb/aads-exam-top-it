#ifndef BORISOV_ARGS_HPP
#define BORISOV_ARGS_HPP
#include <string>

namespace borisov
{
  struct Args
  {
    std::string inFile_;
    std::string outFile_;
    bool inSet_;
    bool outSet_;
    bool valid_;
  };

  Args parseArgs(int argc, char **argv);
}

#endif
