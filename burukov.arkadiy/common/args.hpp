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

  struct DataArgs
  {
    std::string inFile;
    std::string dataFile;
    bool hasIn;
    bool hasData;
    bool valid;
  };

  DataArgs parseDataArgs(int argc, char** argv);

  bool startsWith(const std::string& arg, const std::string& prefix);

}

#endif
