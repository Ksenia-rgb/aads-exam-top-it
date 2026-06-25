#ifndef SAMARIN_COMMON_CLI_HPP
#define SAMARIN_COMMON_CLI_HPP

#include <string>

namespace samarin {
  namespace detail {
    bool takeOption(const std::string & argument, const std::string & prefix, std::string & value);
    bool assignOnce(bool & flag, std::string & target, const std::string & value);
  }
}

#endif
