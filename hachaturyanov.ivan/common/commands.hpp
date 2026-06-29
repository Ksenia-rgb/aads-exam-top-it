#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include "../common/hash_table.hpp"

namespace hachaturyanov
{
  using PersonTable = HashTable< size_t, std::string, std::hash< size_t >, std::equal_to< size_t > >;

  Data readData(std::istream &in, PersonTable &persons);
  void printData(std::ostream &out, PersonTable &persons, List< size_t > order);
}

#endif
