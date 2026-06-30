#ifndef PERSON_HPP
#define PERSON_HPP

#include <cstddef>
#include <iosfwd>
#include <string>
#include <dynamicArray.hpp>

namespace zhuravleva
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  struct Args
  {
    std::string inputFile;
    std::string outputFile;
    bool hasInput;
    bool hasOutput;
  };

  bool contains(const DynamicArray< Person > &persons, size_t id);
  bool readPerson(const std::string &line, Person &person);
  void readPersons(std::istream &input, DynamicArray< Person > &persons, size_t &good, size_t &bad);
  void printPersons(std::ostream &output, const DynamicArray< Person > &persons);
  bool parseArgs(int argc, char *argv[], Args &args);
}

#endif
