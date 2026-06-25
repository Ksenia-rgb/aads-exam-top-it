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
  
}