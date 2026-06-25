#ifndef PERSONS_HPP
#define PERSONS_HPP

#include <cstddef>
#include <iosfwd>
#include <string>

#include "array.hpp"

namespace lukashevich
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  struct ReadStats
  {
    size_t accepted;
    size_t ignored;
  };

  struct ProgramOptions
  {
    std::string inputName;
    std::string outputName;
    bool hasInput;
    bool hasOutput;
  };

  void initReadStats(ReadStats& stats) noexcept;
  void initOptions(ProgramOptions& options);
  bool hasPerson(const Array< Person >& persons, size_t id);
}

#endif
