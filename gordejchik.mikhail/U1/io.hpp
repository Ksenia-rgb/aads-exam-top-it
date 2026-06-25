#ifndef IO_HPP
#define IO_HPP

#include <iostream>
#include <cstddef>
#include "person.hpp"
#include "dynarray.hpp"

namespace gordejchik {
  struct read_result_t {
    size_t success_;
    size_t ignored_;
  };

  read_result_t readPersons(std::istream& in, dynarray_t< person_t >& arr);
  void writePersons(std::ostream& out, const dynarray_t< person_t >& arr);
}

#endif
