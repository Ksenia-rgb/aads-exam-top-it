#include "persons.hpp"

#include <limits>

namespace lukashevich
{
  namespace detail 
  {
    bool isSpace(char ch);
    std::string tri(const std::string& text);
    bool parseUnsigned(const std::string& text, size_t begin, size_t& value, size_t& end);
  }
}

bool lukashevich::detail::isSpace(char ch)
{
  return (ch == ' ') || (ch == '\t') || (ch == '\r');
}

std::string lukashevich::detail::tri(const std::string& text)
{
  size_t begin = 0;

  while((begin < text.size()) && isSpace(text[begin])) {
    ++begin;
  }

  size_t end = text.size();

  while ((end > begin) && isSpace(text[end - 1])) {
    --end;
  }

  return text.substr(begin, end - begin);
}

bool lukashevich::detail::parseUnsigned(const std::string& text, size_t begin, size_t& value, size_t& end)
{
  if ((begin >= text.size()) || (text[begin] < '0') || (text[begin] > '9')) {
    return false;
  }

  size_t res = 0;
  size_t pos = begin;

  while ((pos < text.size()) && (text[pos] >= '0') && (text[pos] <= '9')) {
    const size_t digit = static_cast< size_t >(text[pos] - '0');

    if (res > (std::numeric_limits< size_t >::max() - digit) / 10) {
      return false;
    }

    res = res * 10 + digit;
    ++pos;
  }

  value = res;
  end = pos;
  return true;
}