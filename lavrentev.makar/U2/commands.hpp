#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <cstddef>
#include <string>
#include "../common/Person.hpp"

namespace lavrentev
{
  void anons(Person** persons);
  void deanon(Person** persons, size_t anonId, size_t id);
  void redesc(Person** persons, size_t id, std::string description);
  void desc(Person** persons, size_t id);
  void meets(Person** persons, size_t id);
  void commons(Person** persons, size_t id1, size_t id2);
  void less(Person** persons, size_t time, size_t id);
  void greater(Person** persons, size_t time, size_t id);
  void outPersons(Person** persons, std::string filename);
}

#endif
