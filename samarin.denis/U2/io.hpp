#ifndef SAMARIN_U2_IO_HPP
#define SAMARIN_U2_IO_HPP

#include <iosfwd>

#include "model.hpp"

namespace samarin {
  void readPersons(std::istream & input, dataset_t & data);
  bool readMeetings(std::istream & input, dataset_t & data);
  void writePersons(std::ostream & output, const dataset_t & data);
}

#endif
