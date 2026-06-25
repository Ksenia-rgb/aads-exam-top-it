#include "commands.hpp"

#include <fstream>
#include <stdexcept>

namespace
{
  const char* ANON_PERSON = "<ANON>";

  bool readToken(const std::string& line, size_t& pos, std::string& token)
  {
    while ((pos < line.size()) && lukashevich::detail::isSpace(line[pos])) {
      ++pos;
    }

    if (pos >= line.size()) {
      return false;
    }

    const size_t begin = pos;

    while ((pos < line.size()) && !lukashevich::detail::isSpace(line[pos])) {
      ++pos;
    }

    token = line.substr(begin, pos - begin);
    return true;
  }
}