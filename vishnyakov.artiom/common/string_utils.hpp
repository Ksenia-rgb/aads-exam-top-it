#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <cctype>

namespace vishnyakov
{

inline std::string trimLeft(const std::string& s)
{
  size_t pos = 0;
  while (pos < s.length() && std::isspace(s[pos]))
  {
    ++pos;
  }
  return s.substr(pos);
}

inline std::string trimRight(const std::string& s)
{
  size_t pos = s.length();
  while (pos > 0 && std::isspace(s[pos - 1]))
  {
    --pos;
  }
  return s.substr(0, pos);
}

inline std::string trim(const std::string& s)
{
  return trimRight(trimLeft(s));
}

}

#endif

