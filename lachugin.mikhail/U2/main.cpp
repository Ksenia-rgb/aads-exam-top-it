#include "functionsVector.hpp"
#include <fstream>
#include <iostream>
#include <string>


int main(int argc, char* argv[])
{
  bool hasInput = false;
  bool hasData = false;

  std::string inputName;
  std::string dataName;

  if (argc < 2 || argc > 3)
  {
    std::cerr << "Invalid arguments\n";
    return 0;
  }

  for (int i = 1; i < argc; i++)
  {
    std::string arg = argv[i];

    if (arg.compare(0, 3, "in:") == 0)
    {
      if (hasInput)
      {
        std::cerr << "Invalid arguments\n";
        return 1;
      }

      hasInput = true;
      inputName = arg.substr(3);
    }
    else if (arg.compare(0, 5, "data:") == 0)
    {
      if (hasData)
      {
        std::cerr << "Invalid arguments\n";
        return 1;
      }

      hasData = true;
      dataName = arg.substr(5);
    }
    else
    {
      std::cerr << "Invalid arguments\n";
      return 1;
    }
  }

  if (!hasData)
  {
    std::cerr << "Invalid arguments\n";
    return 1;
  }

  lachugin::Vector< lachugin::Person > persons;
  lachugin::Vector< lachugin::Meeting > meetings;

  lachugin::initVector(persons);
  lachugin::initVector(meetings);
  if (hasInput)
  {
    std::ifstream personFile(inputName);

    if (!personFile)
    {
      std::cerr << "Cannot open file\n";
      lachugin::clearVector(persons);
      lachugin::clearVector(meetings);
      return 2;
    }
    size_t success = 0;
    size_t ignored = 0;

    lachugin::readPersons(personFile, persons, success, ignored);
  }

  std::ifstream dataFile(dataName);

  if (!dataFile)
  {
    std::cerr << "Cannot open file\n";
    lachugin::clearVector(persons);
    lachugin::clearVector(meetings);
    return 2;
  }

  lachugin::Meeting meeting;

  while (true)
  {
    if (!lachugin::readMeeting(dataFile, meeting))
    {
      if (dataFile.eof())
      {
        break;
      }

      std::cerr << "Invalid data\n";

      lachugin::clearVector(persons);
      lachugin::clearVector(meetings);

      return 3;
    }

    lachugin::addPerson(persons, meeting.firstId);
    lachugin::addPerson(persons, meeting.secondId);

    lachugin::addMeeting(meetings, meeting.firstId, meeting.secondId, meeting.time);
  }

  std::string command;
  while (std::cin >> command)
  {
    if (command == "desc")
    {
      size_t id;

      if (!(std::cin >> id))
      {
        std::cout << "INVALID COMMAND\n";
        continue;
      }

      lachugin::desc(persons, id);
    }
    else if (command == "redesc")
    {
      size_t id;

      if (!(std::cin >> id))
      {
        std::cout << "INVALID COMMAND\n";
        continue;
      }

      std::cin >> std::ws;
      if (std::cin.peek() != '"')
      {
        std::cout << "INVALID COMMAND\n";
        continue;
      }

      std::cin.get();
      std::string info;
      std::getline(std::cin, info, '"');
      lachugin::redesc(persons, id, info);
    }
    else if (command == "anons")
    {
      lachugin::anons(persons);
    }
    else if (command == "out-persons")
    {
      std::string fileName;

      if (!(std::cin >> fileName))
      {
        std::cout << "INVALID COMMAND\n";
        continue;
      }
      lachugin::outPersons(persons, fileName);
    }
    else if (command == "meets")
    {
      size_t id;

      if (!(std::cin >> id))
      {
        std::cout << "INVALID COMMAND\n";
        continue;
      }

      lachugin::meets(meetings, id);
    }
    else if (command == "less")
    {
      size_t time;
      size_t id;

      if (!(std::cin >> time >> id))
      {
        std::cout << "INVALID COMMAND\n";
        continue;
      }

      lachugin::less(meetings, time, id);
    }
    else
    {
      std::cout << "INVALID COMMAND\n";
    }
  }

  lachugin::clearVector(persons);
  lachugin::clearVector(meetings);

  return 0;
}
