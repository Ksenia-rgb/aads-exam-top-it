#include <iostream>
#include <fstream>
#include <string>
#include "input_handler.hpp"
#include "person.hpp"
#include "parse_line.hpp"
#include "vector.hpp"

int main(int argc, char* argv[])
{
    if (argc > 3)
    {
      std::cerr << "Invalid arguments." << std::endl;
      return 0;
    }
    std::string inputFileName;
    std::string outputFileName;
    bool hasInputFile = false;
    bool hasOutputFile = false;
    for (int i = 1; i < argc; ++i)
    {
      std::string arg = argv[i];
      if (arg.rfind("in:", 0) == 0 && !hasInputFile)
      {
        inputFileName = arg.substr(3);
        hasInputFile = true;
      }
      else if (arg.rfind("out:", 0) == 0 && !hasOutputFile)
      {
        outputFileName = arg.substr(4);
        hasOutputFile = true;
      }
      else
      {
        std::cerr << "Invalid arguments." << std::endl;
        return 0;
      }
    }
    smirnova::InputHandler inputHandler(inputFileName);
    smirnova::Vector< smirnova::Person > persons;
    size_t validEntries = 0;
    size_t ignoredEntries = 0;
    smirnova::processInput(inputHandler.getInputStream(), persons, validEntries, ignoredEntries);
    if (hasOutputFile)
    {
        std::ofstream output(outputFileName.c_str());
        if (!output)
        {
          std::cerr << "Failed to open output file." << std::endl;
          return 2;
        }
        smirnova::printPersons(persons, output);
    }
    else
    {
      smirnova::printPersons(persons, std::cout);
      
      if (validEntries != 0 || ignoredEntries != 0)
      {
        std::cerr << validEntries << " " << ignoredEntries << std::endl;
      }
      else
      {
        std::cout << '\n';
        std::cerr << "0 0\n";
      }
    }
    return 0;
}

