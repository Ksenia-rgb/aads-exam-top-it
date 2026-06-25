#include "person.hpp"
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
}
bool musorin::parseLine(const std::string & line, Person & person)
{
  std::size_t pos = 0;
  while (pos < line.size() && isSpace(line[pos]))
  {
    ++pos;
  }
  if (pos == line.size() || !isDigit(line[pos]))
  {
    return false;
  }
  std::size_t id = 0;
  while (pos < line.size() && isDigit(line[pos]))
  {
    const std::size_t digit = static_cast< std::size_t >(line[pos] - '0');
    id = id * 10 + digit;
    ++pos;
  }
  if (pos < line.size() && !isSpace(line[pos]))
  {
    return false;
  }
  while (pos < line.size() && isSpace(line[pos]))
  {
    ++pos;
  }
  if (pos == line.size())
  {
    return false;
  }
  person.id = id;
  person.info = line.substr(pos);
  return true;
}
