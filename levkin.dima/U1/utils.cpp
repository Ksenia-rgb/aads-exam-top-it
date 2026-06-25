#include "utils.hpp"
#include <iostream>
#include <string>
#include <cctype>

namespace levkin {
  Pair* reallocate(Vec& v)
  {
    size_t nw_cap = 0;
    if (v.cap == 0) {
      nw_cap = 1;
    } else {
      nw_cap = 2 * v.cap;
    }
    Pair* nw = new Pair[nw_cap];
    for (size_t i = 0; i < v.size; i++) {
      nw[i] = std::move(v.data[i]);
    }
    if (v.data != nullptr) {
      delete[] v.data;
    }
    v.cap = nw_cap;
    v.data = nw;
    return nw;
  }

  void readToVec(Vec& v, std::istream& is, size_t& total, size_t& ignored)
  {
    std::string line;
    while (std::getline(is, line)) {
      size_t idx = 0;
      while (idx < line.length()
             && std::isspace(static_cast< unsigned char >(line[idx]))) {
        idx++;
      }
      size_t id = 0;
      bool hasDigit = false;
      while (idx < line.length()
             && std::isdigit(static_cast< unsigned char >(line[idx]))) {
        id = id * 10 + (line[idx] - '0');
        hasDigit = true;
        idx++;
      }
      if (!hasDigit) {
        ignored++;
        continue;
      }
      if (idx < line.length()
          && !std::isspace(static_cast< unsigned char >(line[idx]))) {
        ignored++;
        continue;
      }
      while (idx < line.length()
             && std::isspace(static_cast< unsigned char >(line[idx]))) {
        idx++;
      }
      if (idx == line.length()) {
        ignored++;
        continue;
      }
      std::string name = line.substr(idx);
      bool is_duplicate = false;
      for (size_t i = 0; i < v.size; ++i) {
        if (v.data[i].first == id) {
          is_duplicate = true;
          break;
        }
      }
      if (is_duplicate) {
        ignored++;
        continue;
      }
      if (v.size >= v.cap) {
        reallocate(v);
      }
      v.data[v.size] = std::make_pair(id, name);
      v.size++;
      total++;
    }
  }
}
