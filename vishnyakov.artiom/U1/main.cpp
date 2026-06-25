#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "person.hpp"
#include "list.hpp"
#include "hash.hpp"
#include "string_utils.hpp"

int main(int argc, char* argv[])
{
  std::string inputFile;
  std::string outputFile;
  bool hasInputArg = false;

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
      hasInputArg = true;
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
  bool hasData = false;

  while (std::getline(*in, line))
  {
    hasData = true;
    std::string trimmed = vishnyakov::trim(line);

    if (trimmed.empty())
    {
      continue;
    }

    size_t pos = 0;
    size_t id = 0;

    while (pos < trimmed.length() && std::isdigit(trimmed[pos]))
    {
      id = id * 10 + (trimmed[pos] - '0');
      ++pos;
    }

    if (pos == 0)
    {
      ++ignored;
      continue;
    }

    while (pos < trimmed.length() && std::isspace(trimmed[pos]))
    {
      ++pos;
    }

    if (pos >= trimmed.length())
    {
      ++ignored;
      continue;
    }

    std::string info = trimmed.substr(pos);

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

  if (hasData || hasInputArg)
  {
    std::cerr << successful << " " << ignored << "\n";
  }

  for (vishnyakov::ListNode< vishnyakov::Person >* current = persons.begin();
       current != persons.end();
       current = current->next)
  {
    *out << current->data.id << " " << current->data.info << "\n";
  }

  return 0;
}

