#include "parse.hpp"

bool novikov::parse(int argc, char* argv[], std::string& input_file, std::string& output_file)
{
  if (argc > 3) {
    return false;
  }

  bool has_in = false;
  bool has_out = false;

  for (int i = 1; i < argc; ++i) {
    std::string arg(argv[i]);
    if (arg.find("in:") == 0) {
      if (has_in) {
        return false;
      }
      input_file = arg.substr(3);
      has_in = true;
    } else if (arg.find("out:") == 0) {
      if (has_out) {
        return false;
      }
      output_file = arg.substr(4);
      has_out = true;
    } else {
      return false;
    }
  }
  return true;
}
