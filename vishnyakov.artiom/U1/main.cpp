#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "person.hpp"
#include "list.hpp"
#include "hash.hpp"

int main(int argc, char* argv[])
{
  std::string inputFile;
  std::string outputFile;

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];

    if (arg.rfind("in:", 0) == 0)
    {
      if (!inputFile.empty())
      {
        std::cerr << "Error: duplicate input file argument\n";
        return 1;
      }
      inputFile = arg.substr(3);
    }
    else if (arg.rfind("out:", 0) == 0)
    {
      if (!outputFile.empty())
      {
        std::cerr << "Error: duplicate output file argument\n";
        return 1;
      }
      outputFile = arg.substr(4);
    }
    else
    {
      std::cerr << "Error: invalid argument\n";
      return 1;
    }
  }

  std::istream* in = &std::cin;
  std::ifstream inputFileStream;

  if (!inputFile.empty())
  {
    inputFileStream.open(inputFile);
    if (!inputFileStream.is_open())
    {
      std::cerr << "Error: cannot open input file\n";
      return 2;
    }
    in = &inputFileStream;
  }

  std::ostream* out = &std::cout;
  std::ofstream outputFileStream;

  if (!outputFile.empty())
  {
    outputFileStream.open(outputFile);
    if (!outputFileStream.is_open())
    {
      std::cerr << "Error: cannot open output file\n";
      return 2;
    }
    out = &outputFileStream;
  }

  vishnyakov::List< vishnyakov::Person > persons;
  vishnyakov::HashSet< size_t > usedIds;
  size_t successful = 0;
  size_t ignored = 0;
  std::string line;

  while (std::getline(*in, line))
  {
    if (line.empty())
    {
      continue;
    }

    size_t pos = 0;
    while (pos < line.length() && std::isspace(line[pos]))
    {
      ++pos;
    }

    if (pos >= line.length())
    {
      continue;
    }

    size_t id = 0;
    bool validId = true;

    while (pos < line.length() && std::isdigit(line[pos]))
    {
      id = id * 10 + (line[pos] - '0');
      ++pos;
    }

    if (pos == 0 || !validId)
    {
      ++ignored;
      continue;
    }

    while (pos < line.length() && std::isspace(line[pos]))
    {
      ++pos;
    }

    if (pos >= line.length())
    {
      ++ignored;
      continue;
    }

    std::string info = line.substr(pos);

    if (info.empty())
    {
      ++ignored;
      continue;
    }

    if (usedIds.has(id))
    {
      ++ignored;
      continue;
    }

    vishnyakov::Person p;
    p.id = id;
    p.info = info;
    persons.pushBack(p);
    usedIds.insert(id);
    ++successful;
  }

  for (vishnyakov::ListNode< vishnyakov::Person >* current = persons.head_; current != nullptr; current = current->next)
  {
    *out << current->data.id << " " << current->data.info << "\n";
  }

  std::cerr << successful << " " << ignored << "\n";

  return 0;
}

