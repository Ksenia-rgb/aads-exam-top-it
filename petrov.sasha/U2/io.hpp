#ifndef IO_HPP
#define IO_HPP

#include <string>
#include "domain.hpp"

namespace petrov
{
  bool readPersonsFromFile(const std::string& filename, DataBase& db);
  int readMeetingsFromFile(const std::string& filename, DataBase& db);
}

#endif