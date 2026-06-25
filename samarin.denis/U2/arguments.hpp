#ifndef SAMARIN_U2_ARGUMENTS_HPP
#define SAMARIN_U2_ARGUMENTS_HPP

#include <string>

namespace samarin {
  struct Options {
    bool hasPersons;
    std::string personsName;
    std::string dataName;
  };

  bool parseArguments(int argc, const char * const * argv, Options & options);
}

#endif
