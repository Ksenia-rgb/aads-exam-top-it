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

      size_t id = 0;
      size_t pos = 0;
      for (char c : line) {
        if (c < '0' || c > '9')
          break;
        id = id * 10 + (c - '0');
        pos++;
      }

      if (pos == 0 || pos == line.length())
        continue;

      std::string info = line.substr(pos);
      size_t start = info.find_first_not_of(" \t");
      if (start == std::string::npos)
        continue;
      info = info.substr(start);

      if (info.empty())
        continue;

      bool exists = false;
      for (size_t i = 0; i < ctx.persons.size; ++i) {
        if (ctx.persons.data[i].id == id) {
          exists = true;
          break;
        }
      }

      if (!exists) {
        Person p{id, info};
        dynarray_push(ctx.persons, p);
      }
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
      if (id1 == id2)
        continue;

      ensure_person(ctx, id1);
      ensure_person(ctx, id2);

      Meeting m{id1, id2, duration};
      dynarray_push(ctx.meetings, m);
    }

    if (file.fail() && !file.eof())
      return false;
    return true;
  }
}
