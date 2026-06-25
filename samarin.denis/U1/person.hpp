#ifndef SAMARIN_U1_PERSON_HPP
#define SAMARIN_U1_PERSON_HPP

#include <cstddef>
#include <string>

namespace samarin {
  struct Person {
    std::size_t id;
    std::string info;
  };
}

#endif
