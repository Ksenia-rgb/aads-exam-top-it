#include <functional>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../common/list.hpp"
#include "../common/htable.hpp"

struct Person {
  size_t id;
  std::string info;
};

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
  std::hash< size_t > hashf;
  volkovich::HashTable< size_t, std::string, std::hash< size_t >, std::equal_to< size_t> >
      htable(hashf);
  std::string line;
  size_t ignored = 0;

  volkovich::List<size_t> ids;

  while (std::getline(*input, line)) {
    size_t id;
    std::stringstream ss(line);
    if (!(ss >> id)) {
      ignored++;
      continue;
    }
    if (htable.has(id)) {
      ignored++;
      continue;
    }
    std::string info;
    ss >> std::ws;
    std::getline(ss, info);
    if (info.empty()) {
      ignored++;
      continue;
    }

    htable.add(id, info);
    ids.pushBack(id);
  }

  volkovich::LIter<size_t> iter = ids.begin();
  for(size_t i =0;i<ids.size();i++) {
    *output << *iter<<' '<< *htable.find(*iter) << '\n';
    ++iter;
  }
}
