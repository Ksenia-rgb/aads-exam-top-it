#ifndef MEET_HPP
#define MEET_HPP
#include "../common/person.hpp"
#include "../common/vector.hpp"
#include <cstddef>

namespace dirko
{
  struct Meet
  {
    size_t first;
    size_t second;
    size_t duration;
  };
  void readMeets(std::istream &input, Vector< Meet > &meets);
  void removeSelfMeets(Vector< Meet > &meets);
  void cmdAnons(std::istream &, std::ostream &output, Vector< Person > &persons, Vector< Meet > &);
  void cmdDeanon(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &meets);
  void cmdRedesc(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &);
  void cmdDesc(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &);
  void cmdMeets(std::istream &input, std::ostream &output, Vector< Person > &, Vector< Meet > &meets);
  void cmdCommons(std::istream &input, std::ostream &output, Vector< Person > &, Vector< Meet > &meets);
  void cmdLess(std::istream &input, std::ostream &output, Vector< Person > &, Vector< Meet > &meets);
  void cmdGreater(std::istream &input, std::ostream &output, Vector< Person > &, Vector< Meet > &meets);
  void cmdOutPersons(std::istream &input, std::ostream &output, Vector< Person > &persons, Vector< Meet > &);
}

#endif
