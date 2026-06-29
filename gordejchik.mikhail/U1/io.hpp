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

  read_result_t readPersons(std::istream& in, dynarray_t< Person >& arr);
  void writePersons(std::ostream& out, const dynarray_t< Person >& arr);
}

#endif
