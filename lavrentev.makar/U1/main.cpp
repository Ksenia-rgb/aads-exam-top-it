#include <iostream>
#include <fstream>
#include <sstream>
#include "functions.hpp"

int main(int argc, char* argv[])
{
  std::string in, out;
  if (!lavrentev::parseArgs(argc, argv, in, out))
  {
    std::cerr << "Input processing error" << "\n";
    return 1;
  }

  size_t cap = 10;
  size_t size = 0;
  size_t skip = 0;

  lavrentev::Person* notes = new lavrentev::Person[cap];
  size_t* ids = new size_t[cap];

  if (!in.empty())
  {
    std::ifstream fileIn(in);
    if (!fileIn.is_open())
    {
      delete[] notes;
      delete[] ids;
      std::cerr << "File open error\n";
      return 2;
    }
    lavrentev::readData(fileIn, &notes, &ids, size, cap, skip);
  }
  else
  {
    lavrentev::readData(std::cin, &notes, &ids, size, cap, skip);
  }

  std::ostringstream buf;
  lavrentev::print(buf, &notes, size);

  if (!out.empty())
  {
    std::ofstream fout(out);
    if (!fout.is_open())
    {
      delete[] notes;
      delete[] ids;
      std::cerr << "File open error\n";
      return 2;
    }
    fout << buf.str();
  }
  else
  {
    std::cout << buf.str();
  }

  std::cerr << size << ' ' << skip << '\n';

  delete[] notes;
  delete[] ids;
  return 0;
}
