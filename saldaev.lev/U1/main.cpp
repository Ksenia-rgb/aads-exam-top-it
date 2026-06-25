#include <fstream>
#include <iostream>
#include <limits>
#include <string>

int main(int argc, char *argv[])
{
  if (argc > 2) {
    std::cerr << "wrong amoung of arguments";
    return 1;
  }

  std::fstream ifile, ofile;

  bool ifl = false;
  bool ofl = false;

  for (int i = 1; i < argc; ++i) {
    const char *arg = argv[i];

    if (arg[0] == 'i' && arg[1] == 'n' && arg[2] == ':') {
      if (ifl) {
        std::cerr << "wrong arguments";
        return 1;
      }
      const char *filename = arg + 3;
      ifile.open(filename);
      if (!ifile.is_open()) {
        std::cerr << "failed to open input file";
        return 2;
      }
      ifl = true;
    } else if (arg[0] == 'o' && arg[1] == 'u' && arg[2] == 't' && arg[3] == ':') {
      if (ofl) {
        std::cerr << "wrong arguments";
        return 1;
      }
      const char *filename = arg + 4;
      ofile.open(filename);
      if (!ofile.is_open()) {
        std::cerr << "failed to open output file";
        return 2;
      }
      ofl = true;
    } else {
      std::cerr << "wrong arguments";
      return 1;
    }
  }

  std::istream &in = ifl ? ifile : std::cin;
  std::ostream &out = ofl ? ofile : std::cout;
}
