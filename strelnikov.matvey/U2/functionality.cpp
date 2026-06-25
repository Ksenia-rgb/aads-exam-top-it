#include <fstream>
#include "context.hpp"
#include "../U1/person.hpp"

namespace strelnikov
{

  int parse_args(int argc, char *argv[], std::string &in_file, std::string &data_file, bool &has_in)
  {
    bool has_data = false;
    has_in = false;

    for (int i = 1; i < argc; ++i) {
      std::string arg = argv[i];
      if (arg.substr(0, 3) == "in:") {
        if (has_in)
          return 1;
        in_file = arg.substr(3);
        has_in = true;
      } else if (arg.substr(0, 5) == "data:") {
        if (has_data)
          return 1;
        data_file = arg.substr(5);
        has_data = true;
      } else {
        return 1;
      }
    }

    if (!has_data)
      return 1;
    return 0;
  }

  bool load_persons(const std::string &filename, Context &ctx)
  {
    std::ifstream file(filename);
    if (!file.is_open())
      return false;

    std::string line;
    while (std::getline(file, line)) {
      if (line.empty())
        continue;

      size_t pos = 0;
      while (pos < line.length() && (line[pos] == ' ' || line[pos] == '\t')) {
        ++pos;
      }

      if (pos >= line.length())
        continue;

      if (line[pos] < '0' || line[pos] > '9')
        continue;

      size_t id = 0;
      bool has_digit = false;
      while (pos < line.length() && line[pos] >= '0' && line[pos] <= '9') {
        id = id * 10 + (line[pos] - '0');
        has_digit = true;
        ++pos;
      }

      if (!has_digit)
        continue;

      while (pos < line.length() && (line[pos] == ' ' || line[pos] == '\t')) {
        ++pos;
      }

      std::string info = "";
      if (pos < line.length()) {
        info = line.substr(pos);
      }

      if (info.empty())
        continue;

      PersonData *existing = context_find_person(ctx, id);
      if (existing != nullptr)
        continue;

      context_ensure_person(ctx, id);
      PersonData *p = context_find_person(ctx, id);
      p->info = info;
    }

    return true;
  }

  bool load_meetings(const std::string &filename, Context &ctx)
  {
    std::ifstream file(filename);
    if (!file.is_open())
      return false;

    size_t id1, id2, duration;
    while (file >> id1 >> id2 >> duration) {
      context_add_meeting(ctx, id1, id2, duration);
    }

    if (file.fail() && !file.eof())
      return false;
    return true;
  }
}
