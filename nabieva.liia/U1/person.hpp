#ifndef PERSON_HPP
#define PERSON_HPP

#include <cstddef>
#include <iosfwd>
#include <string>

namespace nabieva
{
  struct Person
  {
    std::size_t id;
    std::string info;
  };

  struct PersonStorage
  {
    Person* data;
    std::size_t size;
    std::size_t capacity;
  };

  void nabieva::initStorage(PersonStorage& storage)
  {
    storage.data = 0;
    storage.size = 0;
    storage.capacity = 0;
  }

  void nabieva::initStorage(PersonStorage& storage)
  {
    storage.data = 0;
    storage.size = 0;
    storage.capacity = 0;
  }
}

#endif