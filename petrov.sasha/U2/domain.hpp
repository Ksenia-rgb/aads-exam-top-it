#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include <cstddef>
#include <string>

#include "array.hpp"

namespace petrov
{
  struct Person
  {
    std::size_t id;
    std::string info;
    bool hasInfo;
  };

  struct Meeting
  {
    std::size_t first;
    std::size_t second;
    std::size_t time;
  };

  using person_array_t = detail::array_t< Person >;

  using meeting_array_t = detail::array_t< Meeting >;

  struct DataBase
  {
    person_array_t persons;
    meeting_array_t meetings;
  };

  void initDataBase(DataBase & db);
  void destroyDataBase(DataBase & db) noexcept;
}

#endif
