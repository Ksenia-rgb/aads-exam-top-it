#include <iostream>
#include <fstream>
#include <string>

#include "../common/Array.hpp"
#include "../common/Parse.hpp"
#include "Database.hpp"
#include "Commands.hpp"

namespace yalovsky
{
  namespace
  {
    const int statusOk = 0;
    const int statusBadArgs = 1;
    const int statusOpenError = 2;
    const int statusBadData = 3;

    bool startsWith(const std::string& text, const std::string& prefix)
    {
      if (text.size() < prefix.size())
      {
        return false;
      }
      return text.compare(0, prefix.size(), prefix) == 0;
    }

    bool parseArguments(int argc, char** argv, std::string& personsName, bool& hasPersons,
        std::string& dataName, bool& hasData)
    {
      const std::string inPrefix = "in:";
      const std::string dataPrefix = "data:";
      hasPersons = false;
      hasData = false;
      for (int i = 1; i < argc; ++i)
      {
        const std::string arg = argv[i];
        if (startsWith(arg, inPrefix))
        {
          if (hasPersons)
          {
            return false;
          }
          hasPersons = true;
          personsName = arg.substr(inPrefix.size());
        }
        else if (startsWith(arg, dataPrefix))
        {
          if (hasData)
          {
            return false;
          }
          hasData = true;
          dataName = arg.substr(dataPrefix.size());
        }
        else
        {
          return false;
        }
      }
      return hasData;
    }

    void runCommands(std::istream& in, std::ostream& out, Database& db)
    {
      std::string line;
      while (std::getline(in, line))
      {
        size_t pos = 0;
        std::string command;
        if (!readWord(line, pos, command))
        {
          continue;
        }
        bool ok = true;
        if (command == "anons")
        {
          if (!atEnd(line, pos))
          {
            ok = false;
          }
          else
          {
            cmdAnons(out, db);
          }
        }
        else if (command == "deanon")
        {
          size_t anonId = 0;
          size_t id = 0;
          if (!readNumber(line, pos, anonId) || !readNumber(line, pos, id) || !atEnd(line, pos))
          {
            ok = false;
          }
          else
          {
            ok = deanon(db, anonId, id);
          }
        }
        else if (command == "desc")
        {
          size_t id = 0;
          if (!readNumber(line, pos, id) || !atEnd(line, pos))
          {
            ok = false;
          }
          else
          {
            ok = cmdDesc(out, db, id);
          }
        }
        else if (command == "redesc")
        {
          size_t id = 0;
          std::string info;
          if (!readNumber(line, pos, id) || !readQuoted(line, pos, info) || !atEnd(line, pos))
          {
            ok = false;
          }
          else
          {
            ok = cmdRedesc(db, id, info);
          }
        }
        else if (command == "meets")
        {
          size_t id = 0;
          if (!readNumber(line, pos, id) || !atEnd(line, pos))
          {
            ok = false;
          }
          else
          {
            ok = cmdMeets(out, db, id);
          }
        }
        else if (command == "commons")
        {
          size_t first = 0;
          size_t second = 0;
          if (!readNumber(line, pos, first) || !readNumber(line, pos, second) || !atEnd(line, pos))
          {
            ok = false;
          }
          else
          {
            ok = cmdCommons(out, db, first, second);
          }
        }
        else if (command == "less" || command == "greater")
        {
          size_t time = 0;
          size_t id = 0;
          if (!readNumber(line, pos, time) || !readNumber(line, pos, id) || !atEnd(line, pos))
          {
            ok = false;
          }
          else
          {
            ok = cmdBounded(out, db, id, time, command == "greater");
          }
        }
        else if (command == "out-persons")
        {
          std::string filename;
          if (!readWord(line, pos, filename) || !atEnd(line, pos))
          {
            ok = false;
          }
          else
          {
            ok = cmdOutPersons(db, filename);
          }
        }
        else
        {
          ok = false;
        }
        if (!ok)
        {
          out << "<INVALID COMMAND>" << '\n';
        }
      }
    }
  }
}

int main(int argc, char** argv)
{
  const int minArgs = 2;
  const int maxArgs = 3;
  if (argc > maxArgs)
  {
    std::cerr << "invalid arguments" << '\n';
    return yalovsky::statusOk;
  }
  if (argc < minArgs)
  {
    std::cerr << "invalid arguments" << '\n';
    return yalovsky::statusBadArgs;
  }
  std::string personsName;
  std::string dataName;
  bool hasPersons = false;
  bool hasData = false;
  if (!yalovsky::parseArguments(argc, argv, personsName, hasPersons, dataName, hasData))
  {
    std::cerr << "invalid arguments" << '\n';
    return yalovsky::statusBadArgs;
  }

  yalovsky::Database db = yalovsky::makeDatabase();
  try
  {
    if (hasPersons)
    {
      std::ifstream personsIn(personsName);
      if (!personsIn.is_open())
      {
        yalovsky::freeDatabase(db);
        std::cerr << "cannot open file" << '\n';
        return yalovsky::statusOpenError;
      }
      yalovsky::loadPersons(personsIn, db);
    }

    std::ifstream dataIn(dataName);
    if (!dataIn.is_open())
    {
      yalovsky::freeDatabase(db);
      std::cerr << "cannot open file" << '\n';
      return yalovsky::statusOpenError;
    }
    if (!yalovsky::loadMeetings(dataIn, db))
    {
      yalovsky::freeDatabase(db);
      std::cerr << "bad meeting data" << '\n';
      return yalovsky::statusBadData;
    }

    yalovsky::runCommands(std::cin, std::cout, db);
  }
  catch (...)
  {
    yalovsky::freeDatabase(db);
    std::cerr << "internal error" << '\n';
    return yalovsky::statusOpenError;
  }

  yalovsky::freeDatabase(db);
  return yalovsky::statusOk;
}
