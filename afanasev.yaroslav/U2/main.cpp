#include <person.hpp>
#include <meeting.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

int main(int argc, char * argv[])
{
  using namespace afanasev;

  std::string inFile, dataFile;
  bool hasIn = false, hasData = false;

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    if (arg.rfind("in:", 0) == 0)
    {
      if (hasIn)
      {
        std::cerr << "Duplicate input argument\n";
        return 1;
      }
      std::string name = arg.substr(3);
      if (name.empty())
      {
        std::cerr << "Invalid argument: empty filename\n";
        return 1;
      }
        hasIn = true;
        inFile = name;
      }
      else if (arg.rfind("data:", 0) == 0)
      {
        if (hasData)
        {
          std::cerr << "Duplicate data argument\n";
          return 1;
        }
        std::string name = arg.substr(5);
        if (name.empty())
        {
          std::cerr << "Invalid argument: empty filename\n";
          return 1;
        }
        hasData = true;
        dataFile = name;
      }
      else
      {
      std::cerr << "Invalid argument\n";
      return 1;
    }
  }

  if (!hasData)
  {
    std::cerr << "Missing data argument\n";
    return 1;
  }

  Person * persons = nullptr;
  size_t count = 0, capacity = 0;

  if (hasIn)
  {
    std::ifstream inStream(inFile);
    if (!inStream.is_open())
    {
      std::cerr << "Cannot open input file\n";
      return 2;
    }
    std::string line;
    while (std::getline(inStream, line))
    {
      Person p;
      if (parseLine(line, p))
      {
        if (!existsPerson(persons, count, p.id))
        {
          addPerson(persons, count, capacity, p);
        }
      }
    }
    inStream.close();
  }

  Meeting * meetings = nullptr;
  size_t mCount = 0, mCapacity = 0;

  std::ifstream dataStream(dataFile);
  if (!dataStream.is_open())
  {
    std::cerr << "Cannot open data file\n";
    delete[] persons;
    return 2;
  }

  std::string line;
  while (std::getline(dataStream, line))
  {
    Meeting m;
    if (!parseMeeting(line, m))
    {
      std::cerr << "Invalid meeting data\n";
      delete[] persons;
      delete[] meetings;
      return 3;
    }

    if (m.id1 == m.id2)
    {
      continue;
    }

    if (!existsPerson(persons, count, m.id1))
    {
      Person p{m.id1, ""};
      addPerson(persons, count, capacity, p);
    }

    if (!existsPerson(persons, count, m.id2))
    {
      Person p{m.id2, ""};
      addPerson(persons, count, capacity, p);
    }

    addMeeting(meetings, mCount, mCapacity, m);
  }
  dataStream.close();

  std::string cmdLine;
  while (std::getline(std::cin, cmdLine))
  {
    if (cmdLine.empty())
    {
      continue;
    }
    processCommand(cmdLine, persons, count, capacity, meetings, mCount);
  }

  delete[] persons;
  delete[] meetings;
  return 0;
}
