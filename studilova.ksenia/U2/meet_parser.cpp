#include "person_ops.hpp"
#include "meet.hpp"

#include <cstddef>
#include <cstdlib>
#include <string>

namespace
{
  bool isSpace(char symbol)
  {
    return std::isspace(static_cast< unsigned char >(symbol));
  }

  void skipSpaces(const std::string &line, std::size_t &position)
  {
    while ((position < line.size()) && isSpace(line[position]))
    {
      ++position;
    }
  }

  bool parseNumber(const std::string &line, size_t &position, size_t &number)
  {
    if (position >= line.size())
    {
      return false;
    }

    char *endPointer = nullptr;
    const unsigned long long value = std::strtoull(line.c_str() + position, &endPointer, 10);

    if (endPointer == (line.c_str() + position))
    {
      return false;
    }

    number = static_cast< std::size_t >(value);
    position = static_cast< std::size_t >(endPointer - line.c_str());

    return true;
  }

  bool parseMeetLine(const std::string &line, studilova::Meet &meet)
  {
    size_t position = 0;

    skipSpaces(line, position);

    if (!parseNumber(line, position, meet.firstId_))
    {
      return false;
    }

    skipSpaces(line, position);

    if (!parseNumber(line, position, meet.secondId_))
    {
      return false;
    }

    skipSpaces(line, position);

    if (!parseNumber(line, position, meet.duration_))
    {
      return false;
    }

    skipSpaces(line, position);

    return position == line.size();
  }
}
