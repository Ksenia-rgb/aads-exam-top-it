#ifndef PERSON_IO_HPP
#define PERSON_IO_HPP

#include "person.hpp"

#include <cstddef>
#include <iosfwd>
#include <string>

namespace alekseev
{
  struct ProgramOptions
  {
    const char* inputName;
    const char* outputName;
    bool hasInput;
    bool hasOutput;
  };

  bool parseProgramOptions(int argc, char** argv, ProgramOptions& options);
  bool parsePersonLine(const std::string& line, Person& person);
  void readPersons(
      std::istream& input,
      PersonArray& persons,
      size_t& successCount,
      size_t& ignoredCount);
  void writePersons(std::ostream& output, const PersonArray& persons);
  int runU1(
      int argc,
      char** argv,
      std::istream& input,
      std::ostream& output,
      std::ostream& error);
}

#endif
