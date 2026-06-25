#include <cstddef>
#include <iostream>
#include <string>
#include <utils.hpp>

namespace kondrat
{
  struct Person
  {
    size_t id;
    std::string info;
    bool described;
  };

  struct Meeting
  {
    size_t first;
    size_t second;
    size_t time;
  };

  struct PersonStorage
  {
    Person * data;
    size_t size;
    size_t capacity;
  };

  struct MeetingStorage
  {
    Meeting * data;
    size_t size;
    size_t capacity;
  };

  struct ProgramArgs
  {
    const char * input;
    const char * data;
  };

  bool parseArgs(int argc, char ** argv, ProgramArgs & args);
}

bool kondrat::parseArgs(int argc, char ** argv, ProgramArgs & args)
{
  args.input = nullptr;
  args.data = nullptr;
  if (argc < 2 || argc > 3)
  {
    return false;
  }

  for (int i = 1; i < argc; ++i)
  {
    if (startsWith(argv[i], "in:"))
    {
      if (args.input != nullptr || argv[i][3] == '\0')
      {
        return false;
      }
      args.input = argv[i] + 3;
    }
    else if (startsWith(argv[i], "data:"))
    {
      if (args.data != nullptr || argv[i][5] == '\0')
      {
        return false;
      }
      args.data = argv[i] + 5;
    }
    else
    {
      return false;
    }
  }

  return args.data != nullptr;
}

int main(int argc, char ** argv)
{}
