#include "parsing.hpp"

#include <limits>

namespace muraviev
{
  bool isSeparator(const char symbol)
  {
    return symbol == ' ' || symbol == '\t' || symbol == '\r' ||
        symbol == '\v' || symbol == '\f';
  }

  bool parseSizeValue(const std::string& text, size_t& value)
  {
    if (text.empty())
    {
      return false;
    }
    size_t result = 0;
    const size_t limit = std::numeric_limits< size_t >::max();
    for (size_t index = 0; index < text.size(); ++index)
    {
      if (text[index] < '0' || text[index] > '9')
      {
        return false;
      }
      const size_t digit = text[index] - '0';
      if (result > (limit - digit) / 10)
      {
        return false;
      }
      result = result * 10 + digit;
    }
    value = result;
    return true;
  }

  bool parsePersonLine(const std::string& line, Person& person)
  {
    size_t position = 0;
    while (position < line.size() && line[position] >= '0' &&
        line[position] <= '9')
    {
      ++position;
    }
    size_t id = 0;
    if (!parseSizeValue(line.substr(0, position), id))
    {
      return false;
    }
    while (position < line.size() && isSeparator(line[position]))
    {
      ++position;
    }
    if (position == line.size())
    {
      return false;
    }
    person.id = id;
    person.info = line.substr(position);
    person.hasInfo = true;
    return true;
  }

  bool parseMeetingLine(const std::string& line, Meeting& meeting)
  {
    std::string values[3];
    size_t position = 0;
    for (size_t index = 0; index < 3; ++index)
    {
      while (position < line.size() && isSeparator(line[position]))
      {
        ++position;
      }
      const size_t start = position;
      while (position < line.size() && !isSeparator(line[position]))
      {
        ++position;
      }
      if (start == position)
      {
        return false;
      }
      values[index] = line.substr(start, position - start);
    }
    while (position < line.size() && isSeparator(line[position]))
    {
      ++position;
    }
    if (position != line.size())
    {
      return false;
    }
    return parseSizeValue(values[0], meeting.first) &&
        parseSizeValue(values[1], meeting.second) &&
        parseSizeValue(values[2], meeting.time);
  }

  bool parseOptions(const size_t argc, char** argv, ProgramOptions& options)
  {
    options.hasPersonsFile = false;
    options.hasDataFile = false;
    options.personsFile.clear();
    options.dataFile.clear();
    if (argc < 2 || argc > 3)
    {
      return false;
    }
    for (size_t index = 1; index < argc; ++index)
    {
      const std::string argument = argv[index];
      if (argument.compare(0, 5, "data:") == 0)
      {
        if (options.hasDataFile || argument.size() == 5)
        {
          return false;
        }
        options.hasDataFile = true;
        options.dataFile = argument.substr(5);
      }
      else if (argument.compare(0, 3, "in:") == 0)
      {
        if (options.hasPersonsFile || argument.size() == 3)
        {
          return false;
        }
        options.hasPersonsFile = true;
        options.personsFile = argument.substr(3);
      }
      else
      {
        return false;
      }
    }
    return options.hasDataFile;
  }
}
