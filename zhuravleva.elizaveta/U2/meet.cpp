#include "../U1/person.hpp"
#include "meet.hpp"
#include <istream>
#include <stdexcept>

namespace
{
  bool startsWith(const std::string &str, const char *prefix)
  {
    size_t i = 0;
    while (prefix[i] != '\0')
    {
      if (i >= str.size() || str[i] != prefix[i])
      {
        return false;
      }
      ++i;
    }
    return true;
  }

  bool isSpace(char c)
  {
    return c == ' ' || c == '\t' || c == '\r'
        || c == '\f' || c == '\v';
  }

  bool readNumber(const std::string &line, size_t &pos, size_t &value)
  {
    while (pos < line.size() && isSpace(line[pos]))
    {
      ++pos;
    }
    if (pos == line.size() || line[pos] < '0' || line[pos] > '9')
    {
      return false;
    }
    value = 0;
    while (pos < line.size() && line[pos] >= '0' && line[pos] <= '9')
    {
      value = value * 10 + static_cast< size_t >(line[pos] - '0');
      ++pos;
    }
    return true;
  }

  bool isEmptyLine(const std::string &line)
  {
    for (size_t i = 0; i < line.size(); ++i)
    {
      if (!isSpace(line[i]))
      {
        return false;
      }
    }
    return true;
  }

  bool hasPerson(
      const zhuravleva::DynamicArray< zhuravleva::Person > &persons,
      size_t id)
  {
    for (size_t i = 0; i < persons.size; ++i)
    {
      if (persons.data[i].id == id)
      {
        return true;
      }
    }
    return false;
  }
}

bool zhuravleva::parseArgs(int argc, char *argv[], MeetArgs &args)
{
  args.personsFile = "";
  args.meetsFile = "";
  args.hasPersons = false;

  if (argc < 2 || argc > 3)
  {
    return false;
  }
  bool hasData = false;
  for (int i = 1; i < argc; ++i)
  {
    const std::string arg(argv[i]);

    if (startsWith(arg, "in:"))
    {
      if (args.hasPersons || arg.size() == 3)
      {
        return false;
      }
      args.personsFile = arg.substr(3);
      args.hasPersons = true;
    }
    else if (startsWith(arg, "data:"))
    {
      if (hasData || arg.size() == 5)
      {
        return false;
      }
      args.meetsFile = arg.substr(5);
      hasData = true;
    }
    else
    {
      return false;
    }
  }
  return hasData;
}


bool zhuravleva::readMeet(const std::string &line, Meet &meet)
{
  size_t pos = 0;
  if (!readNumber(line, pos, meet.first))
  {
    return false;
  }

  if (!readNumber(line, pos, meet.second))
  {
    return false;
  }
  if (!readNumber(line, pos, meet.time))
  {
    return false;
  }
  while (pos < line.size() && isSpace(line[pos]))
  {
    ++pos;
  }
  if (pos != line.size())
  {
    return false;
  }
  return true;
}

void zhuravleva::readMeets(
    std::istream &input,
    DynamicArray< Meet > &meets)
{
  std::string line;
  while (std::getline(input, line))
  {
    if (isEmptyLine(line))
    {
      continue;
    }
    Meet meet = {0, 0, 0};
    if (!readMeet(line, meet))
    {
      throw std::invalid_argument("invalid meet");
    }
    if (meet.first != meet.second)
    {
      pushBack(meets, meet);
    }
  }
}

void zhuravleva::addAnonymous(
    DynamicArray< Person > &persons,
    const DynamicArray< Meet > &meets)
{
  for (size_t i = 0; i < meets.size; ++i)
  {
    if (!hasPerson(persons, meets.data[i].first))
    {
      Person person = {meets.data[i].first, ""};
      pushBack(persons, person);
    }
    if (!hasPerson(persons, meets.data[i].second))
    {
      Person person = {meets.data[i].second, ""};
      pushBack(persons, person);
    }
  }
}

void zhuravleva::processCommands(
    std::istream &input,
    std::ostream &output,
    DynamicArray< Person > &persons,
    DynamicArray< Meet > &meets)
{
  std::string command;
  while (input >> command)
  {
    if (command == "anons")
    {
    }
    else if (command == "desc")
    {
    }
    else if (command == "redesc")
    {
    }
    else if (command == "deanon")
    {
    }
    else if (command == "meets")
    {
    }
    else if (command == "commons")
    {
    }
    else if (command == "less")
    {
    }
    else if (command == "greater")
    {
    }
    else if (command == "out-persons")
    {
    }
    else
    {
      output << "<INVALID COMMAND>\n";
      std::string skip;
      std::getline(input, skip);
    }
  }
}
