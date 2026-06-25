#include <iostream>
#include "utils.hpp"
int main(int argc, char* argv[])
{
  if (argc > 3) {
    return 1;
  }
  std::string in_file;
  std::string out_file;
  bool has_in = false;
  bool has_out = false;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg.rfind("in:", 0) == 0) {
      if (has_in)
        return 1;
      in_file = arg.substr(3);
      has_in = true;
    } else if (arg.rfind("out:", 0) == 0) {
      if (has_out)
        return 1;
      out_file = arg.substr(4);
      has_out = true;
    } else {
      return 1;
    }
  }
  levkin::Vec my_vector = {0, 0, nullptr};
  size_t total = 0;
  size_t ignored = 0;
  std::cerr << total - ignored << "\n";
  std::cerr << ignored << "\n";
}
