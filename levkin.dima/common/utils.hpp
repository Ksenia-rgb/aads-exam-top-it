#ifndef UTILS_HPP
#define UTILS_HPP
#include <cstddef>
#include <iosfwd>
#include <utility>
#include <iostream>
#include <string>
#include <limits>
namespace levkin {
  namespace {
    bool isSpaceChar(char ch);
    bool isDigitChar(char ch);

  }
  using Pair = std::pair< size_t, std::string >;

  template < class T >
  struct Vec
  {
    size_t size;
    size_t cap;
    T* data;
  };
  template < class T >
  Pair* reallocate(Vec< T >& v)
  {
    size_t nw_cap = (v.cap == 0) ? 1 : 2 * v.cap;
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

  template < class T >
  void readToVec(Vec< T >& v, std::istream& is, size_t& total, size_t& ignored)
  {
    std::string line;
    while (std::getline(is, line)) {
      if (!line.empty() && line.back() == '\r') {
        line.pop_back();
      }

      bool is_only_spaces = true;
      for (char ch : line) {
        if (!isSpaceChar(ch)) {
          is_only_spaces = false;
          break;
        }
      }
      if (line.empty() || is_only_spaces) {
        continue;
      }
      size_t idx = 0;
      while (idx < line.length() && isSpaceChar(line[idx])) {
        idx++;
      }
      size_t id = 0;
      bool has_digit = false;
      bool overflow = false;
      while (idx < line.length() && isDigitChar(line[idx])) {
        if (id
            > (std::numeric_limits< size_t >::max() - (line[idx] - '0')) / 10) {
          overflow = true;
        }
        id = id * 10 + (line[idx] - '0');
        has_digit = true;
        idx++;
      }
      if (!has_digit || overflow) {
        ignored++;
        continue;
      }
      if (idx < line.length() && !isSpaceChar(line[idx])) {
        ignored++;
        continue;
      }
      while (idx < line.length() && isSpaceChar(line[idx])) {
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
  template < class T >
  void writeFromVec(const Vec< T >& v, std::ostream& os)
  {
    for (size_t i = 0; i < v.size; ++i) {
      os << v.data[i].first << " " << v.data[i].second << "\n";
    }
  }

  template < class T >
  void pushBack(Vec< T >& v, const T& val)
  {
    if (v.size >= v.cap) {
      reallocate(v);
    }
    v.data[v.size] = val;
    v.size++;
  }

  template < class T >
  void freeVec(Vec< T >& v)
  {
    if (v.data != nullptr) {
      delete[] v.data;
      v.data = nullptr;
    }
    v.size = 0;
    v.cap = 0;
  }
}
#endif
