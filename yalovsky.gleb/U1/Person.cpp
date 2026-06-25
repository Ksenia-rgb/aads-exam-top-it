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
}
