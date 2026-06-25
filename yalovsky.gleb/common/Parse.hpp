#ifndef PARSE_HPP
#define PARSE_HPP

#include <cstddef>
#include <string>

namespace yalovsky
{
  void skipSpaces(const std::string& line, size_t& pos);
  bool atEnd(const std::string& line, size_t pos);
  bool readNumber(const std::string& line, size_t& pos, size_t& value);
  bool readWord(const std::string& line, size_t& pos, std::string& word);
  bool readQuoted(const std::string& line, size_t& pos, std::string& value);
}

#endif
