#ifndef PERSON_HPP
#define PERSON_HPP
#include <cstddef>
#include <iosfwd>
#include <string>
#include "vector.hpp"
namespace dirko
{
  struct Person
  {
    size_t id;
    std::string info;
  };
  std::istream &input(std::istream &in, Vector< Person > &persons, size_t &ignored);
  std::ostream &output(std::ostream &out, Vector< Person > &persons);
}

#endif
