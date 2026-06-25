#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
#include <string>

namespace hachaturyanov
{
  struct Person {
    size_t id;
    std::string info;
  };

  struct Data {
    size_t success;
    size_t ignored;
  }
}

#endif
