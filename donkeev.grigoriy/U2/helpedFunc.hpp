#ifndef HELPEDFUNC_HPP
#define HELPEDFUNC_HPP

#include "list.hpp"

namespace donkeev
{
  void pushBack(PersonList&, Person*);
  bool isUniqueId(const PersonList&, size_t);
  bool isNumber(const std::string&);
  std::string nextWord(const std::string&, size_t&);
  void readingPersons(std::istream&, PersonList&, size_t&);
}
#endif
