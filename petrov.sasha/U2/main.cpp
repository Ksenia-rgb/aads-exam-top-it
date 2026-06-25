#include "domain.hpp"
#include "input_args.hpp"
#include "io.hpp"
#include "commands.hpp"

#include <iostream>

int main(int argc, char * argv[])
{
  try
  {
    petrov::ProgramOptions options = {};
    if (!petrov::parseArguments(argc, argv, options))
    {
      std::cerr << "Invalid command line arguments\n";
      return 1;
    }
    petrov::DataBase db =
    {
      { nullptr, 0, 0 },
      { nullptr, 0, 0 }
    };
    petrov::initDataBase(db);
    if (options.hasPersonsFile)
    {
      if (!petrov::readPersonsFromFile(options.personsFile, db))
      {
        std::cerr << "Cannot open persons file\n";
        petrov::destroyDataBase(db);
        return 2;
      }
    }
    int result = petrov::readMeetingsFromFile(options.dataFile, db);
    if (result != 0)
    {
      std::cerr << "Invalid meetings data\n";
      petrov::destroyDataBase(db);
      return result;
    }
    petrov::commandLoop(db);
    petrov::destroyDataBase(db);
    return 0;
  }
  catch (...)
  {
    std::cerr << "Internal error\n";
    return 2;
  }
}
