#ifndef ANON_HPP
#define ANON_HPP
#include <cstddef>
#include <algorithm>
namespace kitserov
{
  struct AnonsContainer {
    size_t* data_;
    size_t size_;
    size_t capacity_;
  };
  void sortAnons(AnonsContainer& c) {
    std::sort(c.data_, c.data_ + c.size_);
  }
}
#endif
