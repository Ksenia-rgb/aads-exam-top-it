#ifndef MEET_HPP
#define MEET_HPP

#include <cstddef>
#include <iosfwd>
#include <string>
#include <dynamicArray.hpp>
#include "person.hpp"

namespace zhuravleva
{
  struct Meet
  {
    size_t first;
    size_t second;
    size_t time;
  };

  struct Args
  {
    std::string personsFile;
    std::string meetsFile;
    bool hasPersons;
  };

  bool parseArgs(int argc, char *argv[], Args &args);

  bool readMeet(const std::string &line, Meet &meet);
  void readMeets(std::istream &input, DynamicArray< Meet > &meets);

  void addAnonymous(
      DynamicArray< Person > &persons,
      const DynamicArray< Meet > &meets);
}

#endif
