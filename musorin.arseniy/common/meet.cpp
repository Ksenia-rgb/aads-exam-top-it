#include "meet.hpp"
namespace
{
bool isSpace(char ch)
{
  return ch == ' ' || ch == '\t';
}
bool isDigit(char ch)
{
  return ch >= '0' && ch <= '9';
}
bool readNumber(const std::string & line, std::size_t & pos, std::size_t & value)
{
  while (pos < line.size() && isSpace(line[pos]))
  {
    ++pos;
  }
  if (pos == line.size() || !isDigit(line[pos]))
  {
    return false;
  }
  std::size_t result = 0;
  while (pos < line.size() && isDigit(line[pos]))
  {
    const std::size_t digit = static_cast< std::size_t >(line[pos] - '0');
    result = result * 10 + digit;
    ++pos;
  }
  value = result;
  return true;
}
}
bool musorin::parseMeetLine(const std::string & line, Meet & meet)
{
  std::size_t pos = 0;
  std::size_t from = 0;
  if (!readNumber(line, pos, from))
  {
    return false;
  }
  std::size_t to = 0;
  if (!readNumber(line, pos, to))
  {
    return false;
  }
  std::size_t duration = 0;
  if (!readNumber(line, pos, duration))
  {
    return false;
  }
  while (pos < line.size() && isSpace(line[pos]))
  {
    ++pos;
  }
  if (pos != line.size())
  {
    return false;
  }
  meet.from = from;
  meet.to = to;
  meet.duration = duration;
  return true;
}
