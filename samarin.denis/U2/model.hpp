#ifndef SAMARIN_U2_MODEL_HPP
#define SAMARIN_U2_MODEL_HPP

#include <cstddef>
#include <string>

#include "list.hpp"

namespace samarin {
  struct Person {
    std::size_t id;
    bool named;
    std::string description;
  };

  struct Meeting {
    std::size_t first;
    std::size_t second;
    std::size_t duration;
  };

  struct Dataset {
    detail::list_t< Person > persons;
    detail::list_t< Meeting > meetings;
  };

  bool insertPerson(Dataset & data, std::size_t id, bool named, const std::string & description);
  Person * findPerson(Dataset & data, std::size_t id);
  void addMeeting(Dataset & data, std::size_t first, std::size_t second, std::size_t duration);
  void clearDataset(Dataset & data);
}

#endif
