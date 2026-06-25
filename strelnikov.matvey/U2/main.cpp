#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "context.hpp"
#include "commands.hpp"

using namespace strelnikov;

int main(int argc, char *argv[])
{
  std::string in_file, data_file;
  bool has_in = false;

  if (parse_args(argc, argv, in_file, data_file, has_in) != 0) {
    std::cerr << "Invalid arguments\n";
    return 1;
  }

  Context ctx;
  context_init(ctx);

  if (has_in) {
    std::ifstream test(in_file);
    if (!test.is_open()) {
      std::cerr << "Cannot open input file\n";
      context_destroy(ctx);
      return 2;
    }
    test.close();
    if (!load_persons(in_file, ctx)) {
      std::cerr << "Error reading persons\n";
      context_destroy(ctx);
      return 2;
    }
  }

  std::ifstream data_test(data_file);
  if (!data_test.is_open()) {
    std::cerr << "Cannot open data file\n";
    context_destroy(ctx);
    return 2;
  }
  data_test.close();

  if (!load_meetings(data_file, ctx)) {
    std::cerr << "Error reading meetings\n";
    context_destroy(ctx);
    return 3;
  }

  std::string cmd;
  while (std::cin >> cmd) {
    bool found = false;
    for (size_t i = 0; i < cmdCnt; ++i) {
      if (cmd == cmds[i].name) {
        found = true;
        bool success = cmds[i].handler(std::cin, std::cout, ctx);
        if (!success) {
          std::cout << "<INVALID COMMAND>\n";
        }
        break;
      }
    }

    if (!found) {
      std::cout << "<INVALID COMMAND>\n";
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  if (!std::cin.eof()) {
    std::cerr << "Bad input!\n";
    context_destroy(ctx);
    return 1;
  }

  context_destroy(ctx);
  return 0;
}
