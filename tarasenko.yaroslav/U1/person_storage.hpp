#ifndef TARASENKO_YAROSLAV_U1_PERSON_STORAGE_HPP
#define TARASENKO_YAROSLAV_U1_PERSON_STORAGE_HPP

#include <cstddef>
#include <memory>

#include "person.hpp"

namespace tarasenko
{
  struct PersonStorage
  {
    std::unique_ptr< Person[] > persons;
    std::size_t size;
    std::size_t capacity;
  };

  PersonStorage makePersonStorage();
  bool containsId(const PersonStorage& storage, std::size_t id);
  void appendPerson(PersonStorage& storage, const Person& person);
}

#endif
