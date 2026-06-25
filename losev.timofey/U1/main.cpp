#include <iostream>
#include <fstream>
#include <stdexcept>

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

int main(int argc, char* argv[])
{
  try
  {
    losev::Args args = losev::parseArgs(argc, argv);

    std::ifstream inFile;
    std::istream* inStream = &std::cin;

    if (args.hasIn)
    {
      inFile.open(args.inFile);
      if (!inFile.is_open())
      {
        std::cerr << "Failed to open input file\n";
        return 2;
      }
      inStream = &inFile;
    }

    losev::Node* people = nullptr;
    size_t successCount = 0;
    size_t ignoredCount = 0;
    losev::processInput(*inStream, people, successCount, ignoredCount);

    if (args.hasOut)
    {
      std::ofstream outFile(args.outFile);
      if (!outFile.is_open())
      {
        std::cerr << "Failed to open output file\n";
        losev::clearList(people);
        return 2;
      }
      losev::printResults(outFile, people);
    }
    else
    {
      losev::printResults(std::cout, people);
    }

    std::cerr << successCount << " " << ignoredCount << "\n";
    losev::clearList(people);
    return 0;
  }
  catch (const std::runtime_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 2;
  }
}
