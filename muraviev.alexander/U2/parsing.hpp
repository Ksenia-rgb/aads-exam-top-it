#ifndef PARSING_HPP
#define PARSING_HPP

#include "models.hpp"

#include <string>

namespace muraviev
{
  bool isSeparator(char symbol);
  bool parseSizeValue(const std::string& text, size_t& value);
  bool parsePersonLine(const std::string& line, Person& person);
  bool parseMeetingLine(const std::string& line, Meeting& meeting);
  bool parseOptions(size_t argc, char** argv, ProgramOptions& options);
}

#endif
