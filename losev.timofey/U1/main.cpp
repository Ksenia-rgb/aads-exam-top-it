#include <iostream>
#include <fstream>
#include <string>

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

  Args parseArgs(int argc, char* argv[]);
  Person parseLine(const std::string& line);
  void processInput(std::istream& in, Node*& people,
                    size_t& successCount, size_t& ignoredCount);
  void printResults(std::ostream& out, const Node* head);
}

static bool parseArgsSimple(int argc, char* argv[], std::string& inFile, std::string& outFile, bool& hasIn, bool& hasOut)
{
  if (argc > 3)
  {
    return false;
  }

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    if (arg.compare(0, 3, "in:") == 0)
    {
      if (hasIn)
        return false;
      hasIn = true;
      inFile = arg.substr(3);
    }
    else if (arg.compare(0, 4, "out:") == 0)
    {
      if (hasOut)
        return false;
      hasOut = true;
      outFile = arg.substr(4);
    }
    else
    {
      return false;
    }
  }
  return true;
}

int main(int argc, char* argv[])
{
  if (argc > 3)
  {
    std::cerr << "Too many arguments\n";
    return 0;
  }
  std::string inFile, outFile;
  bool hasIn = false, hasOut = false;
  if (!parseArgsSimple(argc, argv, inFile, outFile, hasIn, hasOut))
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  std::ifstream inFileStream;
  std::istream* inStream = &std::cin;
  if (hasIn)
  {
    inFileStream.open(inFile);
    if (!inFileStream.is_open())
    {
      std::cerr << "Failed to open input file\n";
      return 2;
    }
    inStream = &inFileStream;
  }
  losev::Node* people = nullptr;
  size_t successCount = 0;
  size_t ignoredCount = 0;
  losev::processInput(*inStream, people, successCount, ignoredCount);
  if (hasIn)
  {
    inFileStream.close();
  }
  std::ofstream outFileStream;
  std::ostream* outStream = &std::cout;
  if (hasOut)
  {
    outFileStream.open(outFile);
    if (!outFileStream.is_open())
    {
      std::cerr << "Failed to open output file\n";
      losev::clearList(people);
      return 2;
    }
    outStream = &outFileStream;
  }
  if (successCount == 0)
  {
    *outStream << '\n';
  }
  else
  {
    losev::printResults(*outStream, people);
  }
  std::cerr << successCount << " " << ignoredCount << "\n";
  losev::clearList(people);
  if (hasOut)
  {
    outFileStream.close();
  }
  return 0;
}
