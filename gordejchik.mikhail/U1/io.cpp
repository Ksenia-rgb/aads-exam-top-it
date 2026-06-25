#include "io.hpp"
#include <string>

static void stripCr(std::string& line)
{
  if (!line.empty() && line.back() == '\r') {
    line.pop_back();
  }
}

static bool hasId(const gordejchik::dynarray_t< gordejchik::person_t >& arr, size_t id)
{
  for (size_t i = 0; i < arr.size_; ++i) {
    if (arr.data_[i].id_ == id) {
      return true;
    }
  }
  return false;
}
