#include <iostream>
#include <limits>
#include "functionality.cpp"
#include "commands.hpp"
#include "context.hpp"

int main(int argc, char *argv[])
{
  using namespace strelnikov;
  std::string in_file, data_file;
  bool has_in = false;

  if (parse_args(argc, argv, in_file, data_file, has_in) != 0) {
    std::cerr << "Invalid arguments\n";
    return 1;
  }

  Context ctx;
  dynarray_init(ctx.persons, 0);
  dynarray_init(ctx.meetings, 0);

  if (has_in) {
    if (!load_persons(in_file, ctx)) {
      std::cerr << "Cannot open in file\n";
      dynarray_destroy(ctx.persons);
      dynarray_destroy(ctx.meetings);
      return 2;
    }
  }

  if (!load_meetings(data_file, ctx)) {
    std::cerr << "Cannot open data file or bad data\n";
    dynarray_destroy(ctx.persons);
    dynarray_destroy(ctx.meetings);
    return 3;
  }

  std::string cmd;
  while (std::cin >> cmd) {
    bool fnd = false;
    for (size_t i = 0; i < cmdCnt; ++i) {
      if (cmd == cmds[i].name) {
        fnd = true;
        if (!cmds[i].handler(std::cin, std::cout, ctx)) {
          std::cout << "<INVALID COMMAND>\n";
        }
        break;
      }
    }

    if (!fnd) {
      std::cout << "<INVALID COMMAND>\n";
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  if (!std::cin.eof()) {
    std::cerr << "Bad input!\n";
    dynarray_destroy(ctx.persons);
    dynarray_destroy(ctx.meetings);
    return 1;
  }

  dynarray_destroy(ctx.persons);
  dynarray_destroy(ctx.meetings);
  return 0;
}
