#ifndef SAMARIN_U1_ARGUMENTS_HPP
#define SAMARIN_U1_ARGUMENTS_HPP

#include <string>

namespace samarin {
  struct Options {
    bool hasInput;
    std::string inputName;
    bool hasOutput;
    std::string outputName;
  };

  bool parseArguments(int argc, const char * const * argv, Options & options);
}

#endif
