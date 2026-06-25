#include "utils.hpp"
#include <cctype>

namespace levkin {
  namespace {
    bool isSpaceChar(char ch)
    {
      return std::isspace(static_cast< unsigned char >(ch));
    }
    bool isDigitChar(char ch)
    {
      return std::isdigit(static_cast< unsigned char >(ch));
    }
  }

  void selectionSort(Vec<size_t>& vec) {
    for (size_t i = 0; i < vec.size; ++i) {
      for (size_t j = i + 1; j < vec.size; ++j) {
        if (vec.data[i] > vec.data[j]) {
          std::swap(vec.data[i], vec.data[j]);
        }
      }
    }
  }

}
