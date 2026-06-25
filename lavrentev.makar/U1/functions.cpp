#include "functions.hpp"
#include <fstream>

bool lavrentev::exists(size_t id, size_t ids[], size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    if (ids[i] == id)
    {
      return true;
    }
  }
  return false;
}

void lavrentev::readData(std::istream& in, lavrentev::Person notes[], size_t ids[], size_t& curSize, size_t maxSize)
{
  size_t id;
  std::string info;
  while (curSize < maxSize && in >> id >> info)
  {
    if (!lavrentev::exists(id, ids, curSize))
    {
      notes[curSize].id = id;
      notes[curSize].info = info;
      ids[curSize] = id;
      curSize++;
    }
  }
}

void lavrentev::readfile(std::string name, lavrentev::Person notes[], size_t ids[], size_t maxSize)
{
  size_t currentSize = 0;

  if (!name.empty())
  {
    std::ifstream file(name);
    if (!file.is_open())
    {
      throw std::runtime_error("File open error");
    }
    lavrentev::readData(file, notes, ids, currentSize, maxSize);
  }
  else
  {
    lavrentev::readData(std::cin, notes, ids, currentSize, maxSize);
  }
}

bool lavrentev::parseArgs(int argc, char* argv[], std::string inFile, std::string outFile)
{
  if (argc > 3)
  {
    return false;
  }

  bool hasIn = false;
  bool hasOut = false;

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    if (arg.rfind("in:", 0) == 0)
    {
      if (hasIn)
      {
        return false;
      }
      hasIn = true;
      inFile = arg.substr(3);
      if (inFile.empty())
      {
        return false;
      }
    }
    else if (arg.rfind("out:", 0) == 0)
    {
      if (hasOut)
      {
        return false;
      }
      hasOut = true;
      outFile = arg.substr(4);
      if (outFile.empty())
      {
        return false;
      }
    }
    else
    {
      return false;
    }
  }
  return true;
}
