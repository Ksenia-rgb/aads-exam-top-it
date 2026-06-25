#include "person.hpp"
#include <ostream>
#include <istream>

namespace
{
  bool isSpace(char symbol)
  {
    return symbol == ' ' || symbol == '\t' || symbol == '\r'
        || symbol == '\f' || symbol == '\v';
  }

  std::string getInfo(const std::string &line, size_t pos)
  {
    while (pos < line.size() && isSpace(line[pos]))
    {
      ++pos;
    }
    return line.substr(pos);
  }

  bool startsWith(const std::string &line, const char *prefix)
  {
    size_t pos = 0;
    while (prefix[pos] != '\0')
    {
      if (pos >= line.size() || line[pos] != prefix[pos])
      {
        return false;
      }
      ++pos;
    }
    return true;
  }
}

bool zhuravleva::contains(const DynamicArray< Person > &persons, size_t id)
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

bool zhuravleva::readPerson(const std::string &line, Person &person)
{
  size_t pos = 0;
  while (pos < line.size() && isSpace(line[pos]))
  {
    ++pos;
  }
  if (pos == line.size() || line[pos] < '0' || line[pos] > '9')
  {
    return false;
  }
  size_t id = 0;
  while (pos < line.size() && line[pos] >= '0' && line[pos] <= '9')
  {
    id = id * 10 + static_cast< size_t >(line[pos] - '0');
    ++pos;
  }
  const std::string info = getInfo(line, pos);
  if (info.empty())
  {
    return false;
  }
  person.id = id;
  person.info = info;
  return true;
}

void zhuravleva::readPersons(
    std::istream &input,
    DynamicArray< Person > &persons,
    size_t &good,
    size_t &bad)
{
  std::string line;
  while (std::getline(input, line))
  {
    Person person = {0, ""};
    if (!readPerson(line, person) || contains(persons, person.id))
    {
      ++bad;
    }
    else
    {
      pushBack(persons, person);
      ++good;
    }
  }
}

void zhuravleva::printPersons(std::ostream &output, const DynamicArray< Person > &persons)
{
  for (size_t i = 0; i < persons.size; ++i)
  {
    output << persons.data[i].id << " " << persons.data[i].info << "\n";
  }
}

bool zhuravleva::parseArgs(int argc, char *argv[], Args &args)
{
  args.inputFile = "";
  args.outputFile = "";
  args.hasInput = false;
  args.hasOutput = false;
  if (argc > 3)
  {
    return false;
  }
  for (int i = 1; i < argc; ++i)
  {
    const std::string arg(argv[i]);
    if (startsWith(arg, "in:"))
    {
      if (args.hasInput || arg.size() == 3)
      {
        return false;
      }
      args.inputFile = arg.substr(3);
      args.hasInput = true;
    }
    else if (startsWith(arg, "out:"))
    {
      if (args.hasOutput || arg.size() == 4)
      {
        return false;
      }
      args.outputFile = arg.substr(4);
      args.hasOutput = true;
    }
    else
    {
      return false;
    }
  }
  return true;
}
