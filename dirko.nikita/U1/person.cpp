#include "person.hpp"
#include "vector.hpp"
#include <cstddef>
#include <iostream>
#include <string>

std::istream &dirko::input(std::istream &in, Vector< Person > &persons)
{
  size_t id = 0;
  in >> id;
  if (!in) {
    return in;
  }
  for (size_t i = 0; i < persons.size; ++i) {
    if (persons.data[i].id == id) {
      in.setstate(std::ios::failbit);
      return in;
    }
    std::string info;
    in >> std::ws;
    std::getline(in, info);
    add(persons, {id, info});
    return in;
  }
  return in;
}
