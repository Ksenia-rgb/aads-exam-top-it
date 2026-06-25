#include <fstream>
#include <iostream>
#include <string>
#include "list.hpp"
#include "person.hpp"
#include "meet.hpp"
namespace
{
struct Options
{
  std::string dataFile;
  std::string personsFile;
  bool hasPersons;
};
bool parseArgs(int argc, char * argv[], Options & options)
{
  options.hasPersons = false;
  bool hasData = false;
  if (argc < 2 || argc > 3)
  {
    return false;
  }
  const std::string dataPrefix = "data:";
  const std::string inPrefix = "in:";
  for (int i = 1; i < argc; ++i)
  {
    const std::string arg = argv[i];
    if (arg.compare(0, dataPrefix.size(), dataPrefix) == 0)
    {
      if (hasData)
      {
        return false;
      }
      const std::string name = arg.substr(dataPrefix.size());
      if (name.empty())
      {
        return false;
      }
      options.dataFile = name;
      hasData = true;
    }
    else if (arg.compare(0, inPrefix.size(), inPrefix) == 0)
    {
      if (options.hasPersons)
      {
        return false;
      }
      const std::string name = arg.substr(inPrefix.size());
      if (name.empty())
      {
        return false;
      }
      options.personsFile = name;
      options.hasPersons = true;
    }
    else
    {
      return false;
    }
  }
  return hasData;
}
bool hasPerson(const musorin::List< musorin::Person > & persons, std::size_t id)
{
  for (const musorin::detail::Node< musorin::Person > * node = persons.head;
    node != nullptr; node = node->next)
  {
    if (node->value.id == id)
    {
      return true;
    }
  }
  return false;
}
void ensurePerson(musorin::List< musorin::Person > & persons, std::size_t id)
{
  if (hasPerson(persons, id))
  {
    return;
  }
  musorin::Person anon{id, ""};
  musorin::pushBack(persons, anon);
}
void loadPersons(std::istream & in, musorin::List< musorin::Person > & persons)
{
  std::string line;
  while (std::getline(in, line))
  {
    musorin::Person person{0, ""};
    if (!musorin::parseLine(line, person))
    {
      continue;
    }
    if (hasPerson(persons, person.id))
    {
      continue;
    }
    musorin::pushBack(persons, person);
  }
}
bool loadMeets(std::istream & in, musorin::List< musorin::Person > & persons,
  musorin::List< musorin::Meet > & meets)
{
  std::string line;
  while (std::getline(in, line))
  {
    if (line.empty())
    {
      continue;
    }
    musorin::Meet meet{0, 0, 0};
    if (!musorin::parseMeetLine(line, meet))
    {
      return false;
    }
    if (meet.from == meet.to)
    {
      continue;
    }
    ensurePerson(persons, meet.from);
    ensurePerson(persons, meet.to);
    musorin::pushBack(meets, meet);
  }
  return true;
}
}
int main(int argc, char * argv[])
{
  Options options{"", "", false};
  if (!parseArgs(argc, argv, options))
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  musorin::List< musorin::Person > persons;
  musorin::initList(persons);
  musorin::List< musorin::Meet > meets;
  musorin::initList(meets);
  if (options.hasPersons)
  {
    std::ifstream personsStream(options.personsFile);
    if (!personsStream.is_open())
    {
      std::cerr << "Cannot open persons file\n";
      musorin::clear(persons);
      musorin::clear(meets);
      return 2;
    }
    loadPersons(personsStream, persons);
  }
  std::ifstream dataStream(options.dataFile);
  if (!dataStream.is_open())
  {
    std::cerr << "Cannot open data file\n";
    musorin::clear(persons);
    musorin::clear(meets);
    return 2;
  }
  if (!loadMeets(dataStream, persons, meets))
  {
    std::cerr << "Invalid meets data\n";
    musorin::clear(persons);
    musorin::clear(meets);
    return 3;
  }
  musorin::clear(persons);
  musorin::clear(meets);
  return 0;
}
