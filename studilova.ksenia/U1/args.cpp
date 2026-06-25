#include "args.hpp"

namespace
{
  bool hasPrefix(const std::string &text, const std::string &prefix)
  {
    if (text.size() < prefix.size())
    {
      return false;
    }

    for (std::size_t i = 0; i < prefix.size(); ++i)
    {
      if (text[i] != prefix[i])
      {
        return false;
      }
    }

    return true;
  }

  std::string removePrefix(const std::string &text, const std::string &prefix)
  {
    std::string result;

    for (std::size_t i = prefix.size(); i < text.size(); ++i)
    {
      result += text[i];
    }

    return result;
  }
}

studilova::Args studilova::parseArgs(int argc, char *argv[])
{
  Args args{ "", "", false, false, true };

  if ((argc - 1) > 2)
  {
    args.valid_ = false;
    return args;
  }

  const std::string inputPrefix = "in:";
  const std::string outputPrefix = "out:";

  for (int i = 1; i < argc; ++i)
  {
    const std::string argument = argv[i];

    if (hasPrefix(argument, inputPrefix))
    {
      if (args.hasInput_)
      {
        args.valid_ = false;
        return args;
      }

      args.inputFile_ = removePrefix(argument, inputPrefix);

      if (args.inputFile_.empty())
      {
        args.valid_ = false;
        return args;
      }

      args.hasInput_ = true;
    }
    else if (hasPrefix(argument, outputPrefix))
    {
      if (args.hasOutput_)
      {
        args.valid_ = false;
        return args;
      }

      args.outputFile_ = removePrefix(argument, outputPrefix);

      if (args.outputFile_.empty())
      {
        args.valid_ = false;
        return args;
      }

      args.hasOutput_ = true;
    }
    else
    {
      args.valid_ = false;
      return args;
    }
  }

  return args;
}
