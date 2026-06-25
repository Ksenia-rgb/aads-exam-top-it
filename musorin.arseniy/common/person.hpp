#ifndef MUSORIN_PERSON_HPP
#define MUSORIN_PERSON_HPP
#include <cstddef>
#include <string>
namespace musorin
{
struct Person
{
  size_t id;
  std::string info;
  bool parseLine(const std::string & line, Person & person);
};
}
#endif
