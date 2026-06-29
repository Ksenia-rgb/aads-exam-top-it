#include <string>
#include <stdexcept>
#include <iostream>

#include "list.hpp"

namespace losev
{
  struct Args
  {
    std::string inFile;
    std::string outFile;
    bool hasIn;
    bool hasOut;
  };

  Person parseLine(const std::string& line)
  {
    Person result;
    result.id = 0;
    result.info = "";
    if (line.empty())
    {
      return result;
    }
    size_t pos = 0;
    while (pos < line.length() && (line[pos] == ' ' || line[pos] == '\t'))
    {
      ++pos;
    }
    if (pos >= line.length())
    {
      return result;
    }
    std::string numStr = "";
    while (pos < line.length() && line[pos] >= '0' && line[pos] <= '9')
    {
      numStr += line[pos];
      ++pos;
    }
    if (numStr.empty())
    {
      return result;
    }
    result.id = std::stoull(numStr);
    while (pos < line.length() && (line[pos] == ' ' || line[pos] == '\t'))
    {
      ++pos;
    }
    if (pos >= line.length())
    {
      result.info = "";
      return result;
    }
    result.info = line.substr(pos);
    return result;
  }

  void processInput(std::istream& in, Node*& people,
                    size_t& successCount, size_t& ignoredCount)
  {
    std::string line;
    while (std::getline(in, line))
    {
      if (line.empty())
      {
        continue;
      }
      Person p = parseLine(line);
      if (p.id == 0 && p.info.empty())
      {
        ++ignoredCount;
        continue;
      }
      if (p.info.empty())
      {
        ++ignoredCount;
        continue;
      }
      if (findId(people, p.id))
      {
        ++ignoredCount;
        continue;
      }
      pushBack(people, p);
      ++successCount;
    }
  }

  void printResults(std::ostream& out, const Node* head)
  {
    const Node* current = head;
    while (current != nullptr)
    {
      out << current->data.id << " " << current->data.info << "\n";
      current = current->next;
    }
  }

  Args parseArgs(int argc, char* argv[])
  {
    Args result;
    result.hasIn = false;
    result.hasOut = false;
    for (int i = 1; i < argc; ++i)
    {
      std::string arg = argv[i];

      if (arg.substr(0, 3) == "in:")
      {
        if (result.hasIn)
        {
          throw std::invalid_argument("Duplicate in: argument");
        }
        result.inFile = arg.substr(3);
        result.hasIn = true;
      }
      else if (arg.substr(0, 4) == "out:")
      {
        if (result.hasOut)
        {
          throw std::invalid_argument("Duplicate out: argument");
        }
        result.outFile = arg.substr(4);
        result.hasOut = true;
      }
      else
      {
        throw std::invalid_argument("Invalid argument: " + arg);
      }
    }
    return result;
  }
}
