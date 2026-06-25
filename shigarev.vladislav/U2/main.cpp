#include "parseargs.hpp"
#include "personio.hpp"
#include "meeting.hpp"
#include "interactive.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
  shigarev::Args args;
  if (!shigarev::parseArgs(argc, argv, args)) {
    std::cerr << "Invalid arguments\n";
    return 1;
  }

  shigarev::DynArray< shigarev::Person > persons =
      shigarev::createDynArray< shigarev::Person >(8);

  if (args.hasInputFile) {
    std::ifstream inFile(args.inputFile.c_str());
    if (!inFile.is_open()) {
      std::cerr << "Cannot open input file\n";
      return 2;
    }
    shigarev::ReadResult result = shigarev::readPersons(inFile);
    inFile.close();
    persons = result.persons;
  }

  shigarev::DynArray< shigarev::Meeting > meetings =
      shigarev::createDynArray< shigarev::Meeting >(16);

  std::ifstream dataFile(args.dataFile.c_str());
  if (!dataFile.is_open()) {
    std::cerr << "Cannot open data file\n";
    shigarev::destroyDynArray(persons);
    return 2;
  }
  if (!shigarev::readMeetings(dataFile, meetings)) {
    std::cerr << "Invalid meeting data\n";
    shigarev::destroyDynArray(persons);
    shigarev::destroyDynArray(meetings);
    return 3;
  }
  dataFile.close();

  for (size_t i = 0; i < meetings.size_; ++i) {
    const shigarev::Meeting& m = meetings.data_[i];
    shigarev::ensurePersonExists(persons, m.id1);
    shigarev::ensurePersonExists(persons, m.id2);
  }

  shigarev::runInteractive(persons, meetings);

  shigarev::destroyDynArray(persons);
  shigarev::destroyDynArray(meetings);
  return 0;
}
