#include "person_io.hpp"
#include <istream>
#include <ostream>
#include <string>
#include <cstddef>
#include <climits>

std::istream& vasyakin::readPerson(std::istream& in, vasyakin::Person& person, bool& valid)
{
  valid = false;
  std::string line;

  if (!std::getline(in, line))
  {
    return in;
  }

  if (!line.empty() && line.back() == '\r')
  {
    line.pop_back();
  }

  std::size_t pos = 0;
  while (pos < line.size() && (line[pos] == ' ' || line[pos] == '\t'))
  {
    ++pos;
  }

  std::size_t id = 0;
  bool hasDigit = false;

  while (pos < line.size() && line[pos] >= '0' && line[pos] <= '9')
  {
    if (id > SIZE_MAX / 10 || (id == SIZE_MAX / 10 &&
      static_cast< std::size_t >(line[pos] - '0') > SIZE_MAX % 10))
    {
      return in;
    }

    id = id * 10 + static_cast< std::size_t >(line[pos] - '0');
    hasDigit = true;
    ++pos;
  }

  if (!hasDigit)
  {
    return in;
  }

  if (pos < line.size() && line[pos] != ' ' && line[pos] != '\t')
  {
    return in;
  }

  while (pos < line.size() && (line[pos] == ' ' || line[pos] == '\t'))
  {
    ++pos;
  }

  std::string info = line.substr(pos);
  if (info.empty())
  {
    return in;
  }

  person.id = id;
  person.info = info;
  valid = true;

  return in;
}

std::ostream& vasyakin::writePerson(std::ostream& out, const vasyakin::Person& person)
{
  out << person.id << ' ' << person.info;
  return out;
}
