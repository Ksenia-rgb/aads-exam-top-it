#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "person.hpp"

namespace madieva {
  struct PersonArray {
    Person * data_;
    size_t size_;
    size_t capacity_;
  };
  PersonArray createArray();

  void destroyArray(PersonArray & arr) noexcept;

  void pushBack(PersonArray & arr, const Person& person);

  size_t getSize(const PersonArray & arr) noexcept;

  Person& at(PersonArray & arr, size_t index);

  const Person& at(const PersonArray & arr, size_t index);
}

#endif
