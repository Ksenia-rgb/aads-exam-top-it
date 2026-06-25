#include "struct.hpp"
#include "functions.hpp"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char const *argv[])
{
  if (argc > 3)
  {
    std::cerr << "many args";
    return 0;
  }

  std::string inFile = "";
  std::string outFile = "";

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];    
    if (arg.length() >= 3 && arg[0] == 'i' && arg[1] == 'n' && arg[2] == ':')
    {
      if (!inFile.empty())
      {
        return 1;
      }
      inFile = argv[i] + 3;
    }
    else if (arg.length() >= 4 && arg[0] == 'o' && arg[1] == 'u' && arg[2] == 't' && arg[3] == ':')
    {
      if (!outFile.empty())
      {
        return 1;
      }
      outFile = argv[i] + 4;
    }
    else
    {
      return 1;
    }
  }

  std::ifstream fin;
  if (!inFile.empty())
  {
    fin.open(inFile);
    if (!fin.is_open())
    {
      return 2;
    }
  }

  std::ofstream fout;
  if (!outFile.empty())
  {
    fout.open(outFile);
    if (!fout.is_open())
    {
      return 2;
    }
  }

  std::istream& in = inFile.empty() ? std::cin : fin;
  std::ostream& out = outFile.empty() ? std::cout : fout;
  petrov::Data myData{nullptr, 0, 0};
  
  petrov::processStream(in, myData);
  petrov::printData(out, myData);
  delete[] myData.data_;

  return 0;
}
