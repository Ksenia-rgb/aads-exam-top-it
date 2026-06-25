#ifndef ARGS_HPP
#define ARGS_HPP

#include <string>

namespace burukov
{

  struct Args
  {
    std::string inFile;
    std::string outFile;
    bool hasIn;
    bool hasOut;
    bool valid;
  };

  Args parseArgs(int argc, char** argv);

}

#endif
