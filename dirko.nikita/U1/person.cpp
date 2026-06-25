#include "person.hpp"
#include "vector.hpp"
#include <cstddef>
#include <iostream>
#include <limits>
#include <string>

std::istream &dirko::input(std::istream &in, Vector< Person > &persons)
{

  size_t id = 0;
  while (in >> id) {
    if (!in) {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    for (size_t i = 0; i < persons.size; ++i) {
      if (persons.data[i].id == id) {
        in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        continue;
      }
    }
    std::string info;
    in >> std::ws;
    std::getline(in, info);
    add(persons, {id, info});
  }
  return in;
}
