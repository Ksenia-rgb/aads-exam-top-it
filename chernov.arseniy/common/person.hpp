#ifndef PERSON_HPP
#define PERSON_HPP

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector.hpp>

namespace chernov {

  struct Person {
    size_t id;
    std::string info;
  };

  size_t findById(const Vector< Person > & persons, size_t id);
}

#endif
