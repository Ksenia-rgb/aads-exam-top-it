#include "Person.hpp"

#include <istream>
#include <ostream>
#include <string>
#include <cctype>

namespace yalovsky
{
  namespace detail
  {
    bool readId(const std::string& line, size_t& pos, size_t& value)
    {
      while (pos < line.size() && std::isspace(static_cast< unsigned char >(line[pos])))
      {
        ++pos;
      }
      const size_t start = pos;
      const size_t decimalBase = 10;
      size_t result = 0;
      while (pos < line.size() && std::isdigit(static_cast< unsigned char >(line[pos])))
      {
        const size_t digit = static_cast< size_t >(line[pos] - '0');
        result = result * decimalBase + digit;
        ++pos;
      }
      if (pos == start)
      {
        return false;
      }
      value = result;
      return true;
    }

    bool readInfo(const std::string& line, size_t pos, std::string& info)
    {
      while (pos < line.size() && std::isspace(static_cast< unsigned char >(line[pos])))
      {
        ++pos;
      }
      if (pos == line.size())
      {
        return false;
      }
      info = line.substr(pos);
      return true;
    }

    bool containsId(const Array< Person >& persons, size_t id)
    {
      for (size_t i = 0; i < persons.size; ++i)
      {
        if (persons.data[i].id == id)
        {
          return true;
        }
      }
      return false;
    }
  }

  void readPersons(std::istream& in, Array< Person >& persons, size_t& accepted, size_t& ignored)
  {
    accepted = 0;
    ignored = 0;
    std::string line;
    while (std::getline(in, line))
    {
      size_t pos = 0;
      size_t id = 0;
      if (!detail::readId(line, pos, id))
      {
        ++ignored;
        continue;
      }
      std::string info;
      if (!detail::readInfo(line, pos, info))
      {
        ++ignored;
        continue;
      }
      if (detail::containsId(persons, id))
      {
        ++ignored;
        continue;
      }
      const Person person{id, info};
      pushBack(persons, person);
      ++accepted;
    }
  }

  void printPersons(std::ostream& out, const Array< Person >& persons)
  {
    for (size_t i = 0; i < persons.size; ++i)
    {
      out << persons.data[i].id << ' ' << persons.data[i].info << '\n';
    }
  }
}
