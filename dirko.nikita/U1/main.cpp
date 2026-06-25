#include <cstddef>
#include <string>
#include <fstream>
#include <iostream>

struct Person
{
  size_t id;
  std::string info;
};

int main(int argc, char *argv[])
{
  if (argc > 3) {
    return 1;
  }

  std::string inFilename = "";
  std::string outFilename = "";
  bool inSet = false;
  bool outSet = false;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];

    if (arg.find("in:") == 0) {
      if (inSet)
        return 1;
      inFilename = arg.substr(3);
      if (inFilename.empty())
        return 1;
      inSet = true;
    } else if (arg.find("out:") == 0) {
      if (outSet)
        return 1;
      outFilename = arg.substr(4);
      if (outFilename.empty())
        return 1;
      outSet = true;
    } else {
      return 1;
    }
  }
  if (inSet) {
    std::ifstream fin(inFilename);
    if (!fin.is_open()) {
      return 2;
    }
  }

  if (outSet) {
    std::ofstream fout(outFilename);
    if (!fout.is_open()) {
      return 2;
    }
  }
}
