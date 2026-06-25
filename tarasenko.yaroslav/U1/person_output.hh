#ifndef TARASENKO_YAROSLAV_U1_PERSON_OUTPUT_HH
#define TARASENKO_YAROSLAV_U1_PERSON_OUTPUT_HH

#include <iosfwd>

#include "person_storage.hh"

namespace tarasenko
{
  void writePersons(std::ostream& output, const PersonStorage& storage);
}

#endif
