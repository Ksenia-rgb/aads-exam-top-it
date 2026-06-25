#include "person_output.hh"

#include <ostream>

void tarasenko::writePersons(std::ostream& output, const PersonStorage& storage)
{
  for (std::size_t index = 0; index < storage.size; ++index) {
    output << storage.persons[index].id << ' ' << storage.persons[index].info << '\n';
  }
}

