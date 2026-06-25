#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(int argc, char* argv[]) {
  if (argc > 3) {
    std::cerr << "Too many args";
    return 2;
  }
  std::istream* input = &std::cin;
  std::ostream* output = &std::cout;
  std::ifstream file_in;
  std::ofstream file_out;

  if (argc >= 2 && argc <= 3) {
    bool out = 0, in = 0;
    for (size_t i = 1; i < argc; i++) {
      std::stringstream ss(argv[i]);
      std::string type, arg;
      std::getline(ss, type, ':');
      std::getline(ss, arg);
      if (arg.empty() && type != "in" && type != "out") {
        arg = type;
        type = "in";
      }

      if (type == "in") {
        if (in == 1) {
          std::cerr << "Double in";
          return 1;
        }
        file_in.open(arg);
        if (!file_in) {
          std::cerr << "Cannot open file";
          return 2;
        }
        input = &file_in;
        in = 1;
      } else if (type == "out") {
        if (out == 1) {
          std::cerr << "Double out";
          return 1;
        }
        file_out.open(arg);
        if (!file_out) {
          std::cerr << "Cannot open file";
          return 2;
        }
        output = &file_out;
        out = 1;
      }
    }
  }
}
