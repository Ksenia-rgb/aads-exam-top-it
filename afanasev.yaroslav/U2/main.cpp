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


  return 0;
}
