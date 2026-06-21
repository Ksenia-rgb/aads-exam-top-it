#include "file_utils.hpp"
#include <fstream>
#include <ostream>
#include <cstring>
#include <iostream>

bool chernikov::parseArguments(int argc, char *argv[], FileConfig &config, std::ostream &errorOutput)
{
  config.inputFile = "";
  config.outputFile = "";
  config.useStdin = true;
  config.useStdout = true;

  if (argc > 3)
  {
    return false;
  }

  bool hasInput = false;
  bool hasOutput = false;

  for (int i = 1; i < argc; ++i)
  {
    if (std::strncmp(argv[i], "in:", 3) == 0)
    {
      if (hasInput)
      {
        return false;
      }
      config.inputFile = argv[i] + 3;
      config.useStdin = false;
      hasInput = true;
    }
    else if (std::strncmp(argv[i], "out:", 4) == 0)
    {
      if (hasOutput)
      {
        return false;
      }
      config.outputFile = argv[i] + 4;
      config.useStdout = false;
      hasOutput = true;
    }
    else
    {
      return false;
    }
  }

  return true;
}

bool chernikov::openFiles(
    const FileConfig &config,
    std::ifstream &inputFileStream,
    std::ofstream &outputFileStream,
    std::istream *&input,
    std::ostream *&output)
{
  if (!config.useStdin)
  {
    inputFileStream.open(config.inputFile);
    if (!inputFileStream.is_open())
    {
      return false;
    }
    input = &inputFileStream;
  }
  else
  {
    input = &std::cin;
  }

  if (!config.useStdout)
  {
    outputFileStream.open(config.outputFile);
    if (!outputFileStream.is_open())
    {
      if (!config.useStdin)
      {
        inputFileStream.close();
      }
      return false;
    }
    output = &outputFileStream;
  }
  else
  {
    output = &std::cout;
  }

  return true;
}

void chernikov::closeFiles(std::ifstream &inputFileStream, std::ofstream &outputFileStream)
{
  if (inputFileStream.is_open())
  {
    inputFileStream.close();
  }
  if (outputFileStream.is_open())
  {
    outputFileStream.close();
  }
}
