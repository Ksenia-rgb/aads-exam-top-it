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
  using namespace vishnyakov;

  if (argc > 3)
  {
    std::cerr << "Too many arguments\n";
    return 0;
  }

  std::string inputFile;
  std::string outputFile;

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];

    if (arg.rfind("in:", 0) == 0)
    {
      if (!inputFile.empty())
      {
        std::cerr << "Invalid arguments\n";
        return 1;
      }
      inputFile = arg.substr(3);
    }
    else if (arg.rfind("out:", 0) == 0)
    {
      if (!outputFile.empty())
      {
        std::cerr << "Invalid arguments\n";
        return 1;
      }
      outputFile = arg.substr(4);
    }
    else
    {
      std::cerr << "Invalid arguments\n";
      return 1;
    }
  }

  std::ifstream inputFileStream;
  if (!inputFile.empty())
  {
    inputFileStream.open(inputFile);
    if (!inputFileStream.is_open())
    {
      std::cerr << "Cannot open input file\n";
      return 2;
    }
  }

  std::istream& in = inputFile.empty() ? std::cin : inputFileStream;

  std::ofstream outputFileStream;
  if (!outputFile.empty())
  {
    outputFileStream.open(outputFile);
    if (!outputFileStream.is_open())
    {
      std::cerr << "Cannot open output file\n";
      return 2;
    }
  }

  std::ostream& out = outputFile.empty() ? std::cout : outputFileStream;

  List< Person > persons;
  HashSet< size_t > usedIds;
  size_t successful = 0;
  size_t ignored = 0;
  std::string line;
  bool hasData = false;

  while (std::getline(in, line))
  {
    hasData = true;

    size_t first = line.find_first_not_of(" \t");
    if (first == std::string::npos)
    {
      continue;
    }

    size_t space = line.find_first_of(" \t", first);
    if (space == std::string::npos)
    {
      ++ignored;
      continue;
    }

    std::string idStr = line.substr(first, space - first);
    size_t descStart = line.find_first_not_of(" \t", space);
    if (descStart == std::string::npos)
    {
      ++ignored;
      continue;
    }

    std::string info = line.substr(descStart);
    if (info.find_first_not_of(" \t") == std::string::npos)
    {
      ++ignored;
      continue;
    }

    size_t id = 0;
    bool validId = true;
    for (size_t i = 0; i < idStr.length(); ++i)
    {
      if (!std::isdigit(idStr[i]))
      {
        validId = false;
        break;
      }
      id = id * 10 + (idStr[i] - '0');
    }

    if (!validId)
    {
      ++ignored;
      continue;
    }

    if (usedIds.has(id))
    {
      ++ignored;
      continue;
    }

    Person p;
    p.id = id;
    p.info = info;
    persons.pushBack(p);
    usedIds.insert(id);
    ++successful;
  }

  if (!inputFile.empty())
  {
    inputFileStream.close();
  }

  if (persons.size() > 0)
  {
    ListNode< Person >* current = persons.begin();
    out << current->data.id << " " << current->data.info;
    current = current->next;

    while (current != nullptr)
    {
      out << "\n" << current->data.id << " " << current->data.info;
      current = current->next;
    }
    out << "\n";
  }

  std::cerr << successful << " " << ignored << "\n";

  return 0;
}

