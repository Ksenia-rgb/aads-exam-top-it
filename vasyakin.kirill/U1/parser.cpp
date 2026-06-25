#include "parser.hpp"
#include <cctype>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <cstddef>
#include <cstdint>

bool vasyakin::parseLine(const std::string& line, vasyakin::Person& person)
{
  std::string cleanLine = line;
  if (!cleanLine.empty() && cleanLine.back() == '\r')
  {
    cleanLine.pop_back();
  }

  size_t pos = 0;
  size_t len = cleanLine.size();

  while (pos < len && std::isspace(static_cast< unsigned char >(cleanLine[pos])))
  {
    ++pos;
  }

  if (pos >= len)
  {
    return false;
  }

  if (cleanLine[pos] == '-')
  {
    return false;
  }

  char* endPtr = nullptr;
  errno = 0;
  unsigned long long id = std::strtoull(cleanLine.c_str() + pos, &endPtr, 10);

  if (endPtr == cleanLine.c_str() + pos)
  {
    return false;
  }

  if (errno == ERANGE || id > SIZE_MAX)
  {
    return false;
  }

  size_t afterNum = static_cast< size_t >(endPtr - cleanLine.c_str());

  if (afterNum >= len)
  {
    return false;
  }

  if (!std::isspace(static_cast< unsigned char >(cleanLine[afterNum])))
  {
    return false;
  }

  pos = afterNum;

  while (pos < len && std::isspace(static_cast< unsigned char >(cleanLine[pos])))
  {
    ++pos;
  }

  if (pos >= len)
  {
    return false;
  }

  person.id = static_cast< size_t >(id);
  person.info = cleanLine.substr(pos);

  return true;
}
