#ifndef PERSONS_HPP
#define PERSONS_HPP

#include <cstddef>
#include <iosfwd>
#include <string>

#include "array.hpp"

namespace lukashevich
{
  struct Person
  {
    size_t id;
    std::string info;
    bool hasInfo
  };

  bool hasPerson(const Array< Person >& persons, size_t id);
  bool findPersonIndex(const Array< Person >& persons, size_t id, size_t& index);

  namespace detail
  {
    bool isSpace(char ch);
    std::string trim(const std::string& text);
    bool parseUnsigned(const std::string& text, size_t begin, size_t& value, size_t& end);
  }
}

#endif
