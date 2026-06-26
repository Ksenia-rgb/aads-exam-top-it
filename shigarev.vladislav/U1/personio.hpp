#ifndef PERSONIO_HPP
#define PERSONIO_HPP

#include <cstddef>
#include <iosfwd>
#include "person.hpp"
#include "dynarray.hpp"

namespace shigarev {
  struct ReadResult {
    DynArray< Person > persons;
    size_t readCount;
    size_t ignoredCount;
  };

  ReadResult readPersons(std::istream& in);
  void writePersons(std::ostream& out,
      const DynArray< Person >& persons);
  void writeStats(std::ostream& err,
      size_t read, size_t ignored);
}

#endif
