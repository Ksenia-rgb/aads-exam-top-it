#ifndef SAMARIN_COMMON_PARSING_HPP
#define SAMARIN_COMMON_PARSING_HPP

#include <cstddef>
#include <string>
#include <utility>

namespace samarin {
  namespace detail {
    bool isSpaceChar(char symbol);
    void skipSpaces(const std::string & text, std::size_t & position);
    std::pair< bool, std::size_t > readUnsigned(const std::string & text, std::size_t & position);
    bool parseRecord(const std::string & line, std::size_t & id, std::string & description);
  }
}

#endif
