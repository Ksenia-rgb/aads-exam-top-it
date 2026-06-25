#include <person.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char * argv[])
{
  using namespace afanasev;

  if (argc > 3)
  {
    std::cerr << "Too many arguments\n";
    return 1;
  }

  std::string inFile, outFile;
  bool hasIn = false, hasOut = false;

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
    else if (arg.rfind("out:", 0) == 0)
    {
      if (hasOut)
      {
        std::cerr << "Duplicate output argument\n";
        return 1;
      }
      std::string name = arg.substr(3);
      if (name.empty())
      {
        std::cerr << "Invalid argument: empty filename\n";
        return 1;
      }
      hasOut = true;
      outFile = arg.substr(4);
    }
    else
    {
      std::cerr << "Invalid argument\n";
      return 1;
    }
  }

  std::ifstream inStream;
  std::istream * in = &std::cin;
  if (hasIn)
  {
    inStream.open(inFile);
    if (!inStream.is_open())
    {
      std::cerr << "Cannot open input file\n";
      return 2;
    }
    in = &inStream;
  }

  Person * persons = nullptr;
  size_t count = 0;
  size_t capacity = 0;
  size_t ignored = 0;
  bool lines_read = false;
  std::string line;

  while (std::getline(*in, line))
  {
    lines_read = true;
    Person person;
    if (parseLine(line, person))
    {
      if (!existsPerson(persons, count, person.id))
      {
        addPerson(persons, count, capacity, person);
      }
      else
      {
        ++ignored;
      }
    }
    else
    {
      ++ignored;
    }
  }

  if (hasIn)
  {
    inStream.close();
  }

  bool useFile = hasOut && hasIn;
  std::ofstream outStream;
  std::ostream * out = &std::cout;
  if (useFile)
  {
    outStream.open(outFile);
    if (!outStream.is_open())
    {
      std::cerr << "Cannot open output file\n";
      delete[] persons;
      return 2;
    }
    out = &outStream;
  }

  for (size_t i = 0; i < count; ++i)
  {
    *out << persons[i].id << ' ' << persons[i].info << '\n';
  }

  if (useFile)
  {
    outStream.close();
  }

  if (lines_read)
  {
    std::cerr << count << ' ' << ignored << '\n';
  }

  delete[] persons;
  return 0;
}
