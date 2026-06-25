#include "parsing.hpp"

#include <cctype>
#include <cstddef>
#include <string>
#include <utility>

namespace {
  bool isDigitChar(char symbol)
  {
    return std::isdigit(static_cast< unsigned char >(symbol)) != 0;
  }

  void skipSpaces(const std::string & text, std::size_t & position)
  {
    while (position < text.size() && samarin::detail::isSpaceChar(text[position])) {
      ++position;
    }
  }

  std::string trim(const std::string & text)
  {
    std::size_t begin = 0;
    skipSpaces(text, begin);
    std::size_t end = text.size();
    while (end > begin && samarin::detail::isSpaceChar(text[end - 1])) {
      --end;
    }
    return text.substr(begin, end - begin);
  }
}

bool samarin::detail::isSpaceChar(char symbol)
{
  return std::isspace(static_cast< unsigned char >(symbol)) != 0;
}

std::pair< bool, std::size_t > samarin::detail::readUnsigned(const std::string & text,
    std::size_t & position)
{
  const std::size_t base = 10;
  std::size_t value = 0;
  bool hasDigit = false;
  while (position < text.size() && isDigitChar(text[position])) {
    value = value * base + static_cast< std::size_t >(text[position] - '0');
    hasDigit = true;
    ++position;
  }
  return std::make_pair(hasDigit, value);
}

bool samarin::detail::parseRecord(const std::string & line, std::size_t & id,
    std::string & description)
{
  std::size_t position = 0;
  skipSpaces(line, position);
  const std::pair< bool, std::size_t > parsed = readUnsigned(line, position);
  if (!parsed.first) {
    return false;
  }
  const std::string info = trim(line.substr(position));
  if (info.empty()) {
    return false;
  }
  id = parsed.second;
  description = info;
  return true;
}
