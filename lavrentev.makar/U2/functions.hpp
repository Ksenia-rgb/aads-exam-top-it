#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <cstddef>
#include <iosfwd>
#include <string>
#include "../common/Person.hpp"

namespace lavrentev
{
  bool exists(size_t id, size_t ids[], size_t size);
  bool parseLine(const std::string& line, size_t& id, std::string& info);
  void expand(Person** notes, size_t** ids, size_t& maxSize);
  void readData(std::istream& in,
                Person** notes, size_t** ids,
                size_t& curSize, size_t maxSize,
                size_t& skip);
  void readfile(std::string name,
                Person** notes, size_t** ids,
                size_t maxSize,
                size_t& skip);
  void print(std::ostream& out, Person** notes, size_t currentSize);
  bool parseArgs(int argc, char* argv[], std::string& inFile, std::string& outFile);
}

#endif
