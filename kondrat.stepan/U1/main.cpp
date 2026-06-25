#include <cstddef>
#include <string>

namespace kondrat
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  struct PersonStorage
  {
    Person * data;
    size_t size;
    size_t capacity;
  };

  struct ProgramArgs
  {
    const char * input;
    const char * output;
  };

  bool startsWith(const char * value, const char * prefix);
  bool parseArgs(int argc, char ** argv, ProgramArgs & args);
}

bool kondrat::startsWith(const char * value, const char * prefix)
{
  while (*prefix != '\0')
  {
    if (*value != *prefix)
    {
      return false;
    }
    ++value;
    ++prefix;
  }
  return true;
}

bool kondrat::parseArgs(int argc, char ** argv, ProgramArgs & args)
{
  args.input = nullptr;
  args.output = nullptr;
  if (argc > 3)
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
    else if (startsWith(argv[i], "out:"))
    {
      if (args.output != nullptr || argv[i][4] == '\0')
      {
        return false;
      }
      args.output = argv[i] + 4;
    }
    else
    {
      return false;
    }
  }

  return true;
}

int main(int argc, char ** argv)
{}
