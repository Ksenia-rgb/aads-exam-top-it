#ifndef PARSEARGS_HPP
#define PARSEARGS_HPP

#include <string>

namespace shigarev {
  struct Args {
    std::string inputFile;
    std::string dataFile;
    bool hasInputFile;
    bool hasDataFile;
  };

  bool parseArgs(int argc, const char* const* argv,
      Args& args);
}

#endif
