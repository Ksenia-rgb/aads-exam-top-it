#include <iostream>
#include <fstream>
#include <sstream>

void setNames(std::string filename, std::string& inName, std::string&outName, bool& hasIn, bool& hasOut)
{
  std::string prefix = arg.substr(0, 3);
  std::string filename = arg.substr(3);
  std::string prefix2 = arg.substr(0, 4);
  std::string filename2 = arg.substr(4);
  if (filename == "" || (filename == ":" && prefix == "out")
  {
    throw std::logic_error("empty name");
  }
  if (prefix == "in:")
  {
    if (hasIn)
    {
      throw std::logic_error("2 ins");
    }
    inName = filename;
  }
  else if (prefix2 == "out")
  {
    if (hasOut)
    {
      throw std::logic_error("2 outs");
    }
    outName = filename2;
  }
  throw std::logic_error("Bad args");
}

int main(int argc, char *argv[])
{
  std::string filename1;
  std::string filename2;
  std::string inName = "";
  std::string outName = "";
  bool hasIn = false;
  bool hasOut = false;
  if (argc > 3)
  {
    return 1;
  }
  for (size_t i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    try
    {
      setNames(arg, inName, outName, hasIn, hasOut);
    }
    catch (const std::logic_error& e)
    {
      return 1;
    }
  }
  std::istream& in;
  std::ostream& out;
  std::ifstream inputFile;
  if (hasIn)
  {
    inputFile.open(inName);
    if (!inputFile.is_open())
    {
      return 2;
    }
    in = inputFile;
  }
  else
  {
    in = std::cin;
  }

  std::ofstream outputFile;
  if (hasOut)
  {
    outputFile.open(outName);
    if (!outputFile.is_open())
    {
      return 2;
    }
    out = outputFile;
  }
  else
  {
    out = std::cout;
  }
}

