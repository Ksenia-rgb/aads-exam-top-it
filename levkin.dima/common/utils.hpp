#ifndef UTILS_HPP
#define UTILS_HPP
#include <cstddef>
#include <iosfwd>
#include <string>
#include <utility>
namespace levkin {
  using Pair = std::pair< size_t, std::string >;

  template < class T >
  struct Vec
  {
    size_t size;
    size_t cap;
    T* data;
  };
  template < class T >
  Pair* reallocate(Vec< T >& v);
  template < class T >
  void readToVec(Vec< T >& v, std::istream& is, size_t& total, size_t& ignored);
  template < class T >
  void writeFromVec(const Vec< T >& v, std::ostream& os);
}
#endif
