#ifndef PERSON_HPP
#define PERSON_HPP

#include <cstddef>
#include <string>

namespace muraviev
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  bool parsePersonLine(const std::string& line, Person& person);
}

#endif
