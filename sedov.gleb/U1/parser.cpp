#include "parser.hpp"
#include <cctype>
#include <cstdlib>
#include <cerrno>
#include <climits>
#include <cstdint>
#include <cstddef>

bool sedov::parseLine(const std::string & line, Person & person)
{
  size_t pos = 0;
  size_t len = line.size();
  while (pos < len && std::isspace(static_cast< unsigned char >(line[pos])))
  {
    ++pos;
  }
  if (pos >= len)
  {
    return false;
  }
  if (line[pos] == '-')
  {
    return false;
  }
  char * endPtr = nullptr;
  errno = 0;
  unsigned long long id = std::strtoull(line.c_str() + pos, &endPtr, 10);
  if (endPtr == line.c_str() + pos)
  {
    return false;
  }
  if (errno == ERANGE || id > SIZE_MAX)
  {
    return false;
  }
  size_t afterNum = endPtr - line.c_str();
  if (afterNum >= len)
  {
    return false;
  }
  if (!std::isspace(static_cast< unsigned char >(line[afterNum])))
  {
    return false;
  }
  pos = afterNum;
  while (pos < len && std::isspace(static_cast< unsigned char >(line[pos])))
  {
    ++pos;
  }
  if (pos >= len)
  {
    return false;
  }
  person.id = static_cast< size_t >(id);
  person.info = line.substr(pos);
  return true;
}
