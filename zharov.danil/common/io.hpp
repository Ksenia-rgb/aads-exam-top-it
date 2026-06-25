#ifndef IO_HPP
#define IO_HPP
#include <istream>
#include <ostream>
#include <string>
#include <array.hpp>
#include <person.hpp>

namespace zharov
{
  bool parseLine(const std::string& str, Person& p);
  bool hasId(const Array< Person >& arr, size_t id);
  void readPersons(std::istream& in, Array< Person >& persons,
    size_t& accepted, size_t& ignored);
  void writePersons(std::ostream& out, const Array< Person >& persons);
  bool parseMeetLine(const std::string& str, Meet& m);
  bool readMeets(std::istream& in, Array< Meet >& meets);
}

#endif
