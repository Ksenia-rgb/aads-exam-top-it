#include <iostream>
#include <fstream>
#include "functions.hpp"

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

bool lavrentev::parseLine(const std::string& line, size_t& id, std::string& info)
{
  size_t i = 0;
  size_t n = line.size();

  while (i < n && (line[i] == ' ' || line[i] == '\t'))
  {
    ++i;
  }

  if (i >= n || line[i] < '0' || line[i] > '9')
  {
    return false;
  }

  id = 0;
  while (i < n && line[i] >= '0' && line[i] <= '9')
  {
    id = id * 10 + static_cast<size_t>(line[i] - '0');
    ++i;
  }

  if (i < n && line[i] != ' ' && line[i] != '\t')
  {
    return false;
  }

  while (i < n && (line[i] == ' ' || line[i] == '\t'))
  {
    ++i;
  }

  if (i >= n)
  {
    return false;
  }

  info = line.substr(i);
  return true;
}

void lavrentev::readData(
  std::istream& in,
  Person** notes,
  size_t** ids,
  size_t& curSize,
  size_t maxSize,
  size_t& skip)
{
  std::string line;
  while (std::getline(in, line))
  {
    size_t id = 0;
    std::string info;

    if (!lavrentev::parseLine(line, id, info))
    {
      ++skip;
      continue;
    }

    if (lavrentev::exists(id, *ids, curSize))
    {
      ++skip;
      continue;
    }

    if (curSize == maxSize)
    {
      lavrentev::expand(notes, ids, maxSize);
    }

    (*notes)[curSize].id = id;
    (*notes)[curSize].info = info;
    (*ids)[curSize] = id;
    ++curSize;
  }
}

void lavrentev::readfile(
  std::string name,
  lavrentev::Person** notes,
  size_t** ids,
  size_t maxSize,
  size_t& skip)
{
  size_t currentSize = 0;

  if (!name.empty())
  {
    std::ifstream file(name);
    if (!file.is_open())
    {
      throw std::runtime_error("File open error");
    }
    lavrentev::readData(file, notes, ids, currentSize, maxSize, skip);
  }
  else
  {
    lavrentev::readData(std::cin, notes, ids, currentSize, maxSize, skip);
  }
}

bool lavrentev::parseArgs(int argc, char* argv[], std::string& inFile, std::string& outFile)
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

void lavrentev::print(std::ostream& out, Person** notes, size_t currentSize)
{
  for (size_t i = 0; i < currentSize; ++i)
  {
    out << (*notes)[i].id << ' ' << (*notes)[i].info << '\n';
  }
}

void lavrentev::expand(Person** notes, size_t** ids, size_t& maxSize)
{
  maxSize *= 2;
  Person* newNotes = new Person[maxSize];
  size_t* newIds = new size_t[maxSize];

  for (size_t i = 0; i < maxSize / 2; ++i)
  {
    newNotes[i] = (*notes)[i];
    newIds[i] = (*ids)[i];
  }

  delete[] *notes;
  delete[] *ids;

  *notes = newNotes;
  *ids = newIds;
}
