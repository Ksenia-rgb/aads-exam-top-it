#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <person.hpp>
#include <list.hpp>
#include <hash.hpp>
#include <string_utils.hpp>

int main(int argc, char* argv[])
{
  using namespace vishnyakov;

  if (argc > 3)
  {
    std::cerr << "Invalid arguments\n";
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

  List< Person > persons;
  HashSet< size_t > usedIds;
  size_t successful = 0;
  size_t ignored = 0;
  std::string line;

  if (!inputFile.empty())
  {
    std::ifstream in(inputFile);
    if (!in.is_open())
    {
      std::cerr << "Cannot open file\n";
      return 2;
    }

    while (std::getline(in, line))
    {
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
  }
  else
  {
    while (std::getline(std::cin, line))
    {
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
  }

  if (!outputFile.empty())
  {
    std::ofstream out(outputFile);
    if (!out.is_open())
    {
      std::cerr << "Cannot open file\n";
      return 2;
    }

    for (ListNode< Person >* current = persons.begin();
         current != persons.end();
         current = current->next)
    {
      out << current->data.id << " " << current->data.info << "\n";
    }

    std::cout << "in file " << outputFile << "\n";
    for (ListNode< Person >* current = persons.begin();
         current != persons.end();
         current = current->next)
    {
      std::cout << current->data.id << " " << current->data.info << "\n";
    }
  }
  else
  {
    for (ListNode< Person >* current = persons.begin();
         current != persons.end();
         current = current->next)
    {
      std::cout << current->data.id << " " << current->data.info << "\n";
    }
  }

  std::cerr << successful << " " << ignored << "\n";

  return 0;
}

