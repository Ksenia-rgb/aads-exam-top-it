#include "person.hpp"

namespace muraviev
{
  bool parsePersonLine(const std::string& line, Person& person)
  {
    if (line.empty() || line[0] < '0' || line[0] > '9')
    {
      return false;
    }
    size_t position = 0;
    size_t id = 0;
    while (position < line.size() && line[position] >= '0' &&
        line[position] <= '9')
    {
      const size_t digit = line[position] - '0';
      id = id * 10 + digit;
      ++position;
    }
    while (position < line.size() &&
        (line[position] == ' ' || line[position] == '\t'))
    {
      ++position;
    }
    if (position == line.size())
    {
      return false;
    }
    person.id = id;
    person.info = line.substr(position);
    return true;
  }
}
