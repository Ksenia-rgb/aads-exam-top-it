#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>

namespace chernov {
  bool parseArgs(int argc, char ** argv, std::string & inFile, std::string & outFile);
}

#endif
