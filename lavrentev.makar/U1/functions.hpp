#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <cstddef>
#include <iostream>
#include "Person.hpp"

namespace lavrentev
{
  bool exists(size_t id, size_t ids[], size_t size);
  void readData(std::istream& in, Person notes[], size_t ids[], size_t& currentSize, size_t maxSize);
  void readfile(std::string name, Person notes[], size_t ids[], size_t maxSize);
  bool parseArgs(int argc, char* argv[], std::string inFile, std::string outFile);
  void print(std::ostream& out, Person notes[], size_t currentSize);
  void expand(Person** notes, size_t** ids, size_t& maxSize);
}

#endif
