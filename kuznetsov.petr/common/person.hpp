#ifndef AADS_EXAM_TOP_IT_PERSON_HPP
#define AADS_EXAM_TOP_IT_PERSON_HPP
#include <cstddef>
#include <string>
#include <darray.hpp>

namespace kuznetsov {

  struct Person {
    size_t id;
    std::string info;
  };

  Person readPerson(std::istream& in, bool& success);
  bool equalPersons(const Person& a, const Person& b);
  darray< Person > readArray(std::istream& in, size_t& cSucces, size_t& cFail);
}

#endif
