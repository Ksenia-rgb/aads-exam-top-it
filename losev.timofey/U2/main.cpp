#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include "../common/person.hpp"
#include "meeting.hpp"
#include "storage.hpp"
#include "args.hpp"
#include "io.hpp"

int main(int argc, char* argv[])
{
  try
  {
    losev::Args args = losev::parseArgs(argc, argv);

    losev::PersonStorage people;
    initPersonStorage(people);

    if (args.hasIn)
    {
      std::ifstream inFile(args.inFile);
      if (!inFile.is_open())
      {
        std::cerr << "Failed to open input file\n";
        return 2;
      }
      losev::readPeople(inFile, people);
    }

    losev::MeetingStorage meetings;
    initMeetingStorage(meetings);

    std::ifstream dataFile(args.dataFile);
    if (!dataFile.is_open())
    {
      std::cerr << "Failed to open data file\n";
      clearPersonStorage(people);
      return 2;
    }
    losev::readMeetings(dataFile, meetings);

    std::string line;
    while (std::getline(std::cin, line))
    {
      if (line.empty())
      {
        continue;
      }
      std::cerr << "<INVALID COMMAND>\n";
    }

    // Очистка
    clearPersonStorage(people);
    clearMeetingStorage(meetings);

    return 0;
  }
  catch (const std::invalid_argument& e)
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
