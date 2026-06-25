#include "utils.hpp"
#include <cctype>

namespace levkin {
  namespace {
    bool isSpaceChar(char ch)
    {
      return std::isspace(static_cast< unsigned char >(ch));
    }
    bool isDigitChar(char ch)
    {
      return std::isdigit(static_cast< unsigned char >(ch));
    }
  }

}
