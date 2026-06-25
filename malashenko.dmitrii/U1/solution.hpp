#include <iostream>
#include <vector.hpp>

namespace malashenko
{
  struct Person {
    size_t id;
    std::string info;
  };

  bool containsId(const Vec<Person> &vec, size_t id);
  bool read_line(std::istream &in, std::string &line);
  size_t parse_line(const std::string &line, size_t &id, std::string &info);
}
