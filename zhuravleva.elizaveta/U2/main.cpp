#include "../U1/person.hpp"
#include "meet.hpp"
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
  zhuravleva::MeetArgs args;

  if (!zhuravleva::parseArgs(argc, argv, args))
  {
    std::cerr << "invalid arguments\n";
    return 1;
  }
  zhuravleva::DynamicArray< zhuravleva::Person > persons;
  zhuravleva::DynamicArray< zhuravleva::Meet > meets;
  zhuravleva::init(persons);
  zhuravleva::init(meets);
  std::ifstream personsFile;
  std::ifstream meetsFile;

  if (args.hasPersons)
  {
    personsFile.open(args.personsFile);
    if (!personsFile)
    {
      std::cerr << "file error\n";
      zhuravleva::destroy(persons);
      zhuravleva::destroy(meets);
      return 2;
    }

    size_t good = 0;
    size_t bad = 0;
    zhuravleva::readPersons(personsFile, persons, good, bad);
  }

  meetsFile.open(args.meetsFile);
  if (!meetsFile)
  {
    std::cerr << "file error\n";
    zhuravleva::destroy(persons);
    zhuravleva::destroy(meets);
    return 2;
  }

  try
  {
    zhuravleva::readMeets(meetsFile, meets);
  }
  catch (...)
  {
    std::cerr << "invalid meet data\n";
    zhuravleva::destroy(persons);
    zhuravleva::destroy(meets);
    return 3;
  }

  zhuravleva::addAnonymous(persons, meets);
  zhuravleva::destroy(persons);
  zhuravleva::destroy(meets);
  return 0;
}
