#include "../common/commands.hpp"
#include "io_utils.hpp"

#include <fstream>

int main(int argc, char** argv)
{
  char* input = nullptr;
  char* output = nullptr;
  if (argc == 1) {
    if (argv[0][0] == 'i' && argv[0][1] == 'n' && argv[0][2] == ':') {
      input = argv[0] + 3;
    } else if (argv[0][0] == 'o' && argv[0][1] == 'u' && argv[0][2] == 't' && argv[0][3] == ':') {
      output = argv[0] + 4;
    } else {
      return 1;
    }
  } else if (argc == 2) {
    if (argv[0][0] == 'i' && argv[0][1] == 'n' && argv[0][2] == ':') {
      input = argv[0] + 3;
      if (argv[1][0] == 'o' && argv[1][1] == 'u' && argv[1][2] == 't' && argv[1][3] == ':') {
        output = argv[1] + 4;
      } else {
        return 1;
      }
    } else if (argv[0][0] == 'o' && argv[0][1] == 'u' && argv[0][2] == 't' && argv[0][3] == ':') {
      output = argv[0] + 4;
      if (argv[1][0] == 'i' && argv[1][1] == 'n' && argv[1][2] == ':') {
        input = argv[1] + 3;
      } else {
        return 1;
      }
    } else {
      return 1;
    }
  } else if (argv > 2) {
    return 1;
  }

  hachaturyanov::PersonTable persons;
  std::pair< List< size_t >, Data > d;

  if (input) {
    std::ifstream ifile(input);
    if (!file) {
      return 2;
    }
    
    d = hachaturyanov::readData(ifile, persons);
  } else {
    d = hachaturyanov::readData(std::cin, persons);
  }

  if (output) {
    std::ofstream ofile(output);
    if (!ofile) {
      return 2;
    }

    printData(ofile, persons, d.first);
  } else {
    printData(std::cout, persons, d.first);
  }

  std::cerr << d.second.success << ' ' << d.second.ignored << '\n';
  return 0;
}
