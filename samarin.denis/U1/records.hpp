#ifndef SAMARIN_U1_RECORDS_HPP
#define SAMARIN_U1_RECORDS_HPP

#include <cstddef>
#include <iosfwd>

#include "list.hpp"
#include "person.hpp"

namespace samarin {
  struct counts_t {
    std::size_t accepted;
    std::size_t ignored;
  };

  counts_t readRecords(std::istream & input, detail::list_t< Person > & records);
  void writeRecords(std::ostream & output, const detail::list_t< Person > & records);
}

#endif
