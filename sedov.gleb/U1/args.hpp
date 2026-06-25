#ifndef ARGS_HPP
#define ARGS_HPP
#include <string>

namespace sedov
{
  bool hasPrefix(const std::string & arg, const std::string & prefix) noexcept;
  std::string stripPrefix(const std::string & arg, const std::string & prefix);

  struct Args
  {
    std::string inFile;
    std::string outFile;
    bool hasIn;
    bool hasOut;
    bool valid;
  };

  Args parseArgs(int argc, char ** argv);
}

#endif
