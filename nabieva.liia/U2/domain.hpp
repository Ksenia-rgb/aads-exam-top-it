#ifndef KIRILICH_DOMAIN_HPP
#define KIRILICH_DOMAIN_HPP

#include <cstddef>
#include <string>
#include "dynamic_array.hpp"

namespace kirilich
{
  struct Person
  {
    int id;
    std::string description;
    bool hasDescription;
  };

  struct Meeting
  {
    int firstId;
    int secondId;
    int duration;
  };

  struct Database
  {
    DynamicArray< Person > persons;
    DynamicArray< Meeting > meetings;
  };

  void init(Database& database);
  void clear(Database& database);
}

#endif