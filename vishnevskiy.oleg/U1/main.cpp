#include <iostream>
#include <fstream>
#include <sstream>
#include "HashTableImpl.hpp"

struct Person
{
  size_t id;
  std::string info;
};

int parseLine(std::istream& in, Person& person)
{
  std::string line;
  if (!std::getline(in, line))
  {
    return 1;
  }
  size_t start = line.find_first_not_of(" \t");
  if (start == std::string::npos)
  {
    person.id = 0;
    person.info = "";
    return 2;
  }
  line = line.substr(start);

  size_t end = line.find_last_not_of(" \t");
  if (end != std::string::npos)
  {
    line = line.substr(0, end + 1);
  }
  size_t delimiterPos = line.find_first_of(" \t");

  if (delimiterPos == std::string::npos)
  {
    person.id = 0;
    person.info = "";
    return 2;
  }
  std::string idStr = line.substr(0, delimiterPos);
  bool isNumber = true;
  for (char c : idStr)
  {
    if (!std::isdigit(c))
    {
      isNumber = false;
      break;
    }
  }

  if (!isNumber || idStr.empty())
  {
    person.id = 0;
    person.info = "";
    return 2;
  }
  try
  {
    person.id = std::stoull(idStr);
  }
  catch (const std::exception& e)
  {
    person.id = 0;
    person.info = "";
    return 2;
  }
  size_t infoStart = line.find_first_not_of(" \t", delimiterPos + 1);
  if (infoStart != std::string::npos)
  {
    person.info = line.substr(infoStart);
    if (person.info.find_first_not_of(" \t\"") == std::string::npos)
    {
      person.id = 0;
      person.info = "";
      return 2;
    }
  }
  else
  {
    person.id = 0;
    person.info = "";
    return 2;
  }
  return 0;
}

void setNames(std::string arg, std::string& inName, std::string&outName, bool& hasIn, bool& hasOut)
{
  std::string prefix = arg.substr(0, 3);
  std::string filename = arg.substr(3);
  std::string prefix2 = arg.substr(0, 4);
  std::string filename2 = arg.substr(4);
  if (filename == "" || (filename == ":" && prefix == "out"))
  {
    throw std::logic_error("empty name");
  }
  if (prefix == "in:")
  {
    if (hasIn)
    {
      throw std::logic_error("2 ins");
    }
    inName = filename;
    hasIn = true;
  }
  else if (prefix2 == "out:")
  {
    if (hasOut)
    {
      throw std::logic_error("2 outs");
    }
    outName = filename2;
    hasOut = true;
  }
  else
  {
    throw std::logic_error("Bad args");
  }
}

size_t hashSizeT(size_t key)
{
  return key;
}

bool equalSizeT(size_t a, size_t b)
{
  return a == b;
}

int main(int argc, char *argv[])
{
  std::string filename1;
  std::string filename2;
  std::string inName = "";
  std::string outName = "";
  bool hasIn = false;
  bool hasOut = false;
  if (argc > 3)
  {
    return 1;
  }
  for (size_t i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    try
    {
      setNames(arg, inName, outName, hasIn, hasOut);
    }
    catch (const std::logic_error& e)
    {
      return 1;
    }
  }

  std::ifstream inputFile;
  std::istream* inPtr = &std::cin;
  if (hasIn)
  {
    inputFile.open(inName);
    if (!inputFile.is_open())
    {
      return 2;
    }
    inPtr = &inputFile;
  }

  std::ofstream outputFile;
  std::ostream* outPtr = &std::cout;
  if (hasOut)
  {
    outputFile.open(outName);
    if (!outputFile.is_open())
    {
      return 2;
    }
    outPtr = &outputFile;
  }

  vishnevskiy::HashTable<size_t, std::string, size_t(*)(size_t), bool(*)(size_t, size_t)> personTable(200, hashSizeT, equalSizeT);
  Person person;
  int parseResult;
  std::cout << "Table size: " << personTable.getSize() << std::endl;

  while ((parseResult = parseLine(*inPtr, person)) != 1)
  {
    std::cout << "Table size: " << personTable.getSize() << std::endl;
    if (parseResult == 2)
    {
      continue;
    }
    if (!personTable.has(person.id))
    {
      try
      {
        personTable.add(person.id, person.info);
      }
      catch (const std::exception& e)
      {
        try
        {
          personTable.rehash(personTable.getCapacity() * 2);
          personTable.add(person.id, person.info);
        }
        catch (const std::exception& ex)
        {
          return 2;
        }
      }
    }
  }

  vishnevskiy::tableIt<size_t, std::string, size_t(*)(size_t), bool(*)(size_t, size_t)> it(&personTable);
  while (it.hasNext())
  {
    *outPtr << it.key() << " " << it.val() << std::endl;
    it.next();
  }

  if (inputFile.is_open()) inputFile.close();
  if (outputFile.is_open()) outputFile.close();

  return 0;
}
