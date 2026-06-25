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

  struct ReadStats
  {
    std::size_t accepted;
    std::size_t ignored;
  };

  void initStorage(PersonStorage& storage);
  void destroyStorage(PersonStorage& storage);
  bool readPersons(std::istream& input, PersonStorage& storage, ReadStats& stats);
  void printPersons(std::ostream& output, const PersonStorage& storage);
}

#endif
