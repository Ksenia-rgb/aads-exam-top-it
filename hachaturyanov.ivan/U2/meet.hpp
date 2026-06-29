#ifndef MEET_HPP
#define MEET_HPP

#include "../common/hash_table.hpp"
#include "person.hpp"
#include <functional>

namespace hachaturyanov {
  using PersonTable = HashTable< size_t, std::string, std::hash< size_t >, std::equal_to< size_t > >;
  using People = std::pair< Person, Person >;
  class Meet {
    HashTable< People, size_t, std::hash< People >, std::equal_to< People > > meets;
    PersonTable people;
  public:
    Meet(List< List< std::string > > data);

    List< size_t > getAnons() const;
  };
}

#endif
