#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <meeting.hpp>
#include <person.hpp>
#include <vector.hpp>

namespace chernov {

  void printAnons(const Vector< size_t > & allIds, const Vector< Person > & persons);
  bool processDeanon(Vector< Person > & persons,
    Vector< Meeting > & meetings,
    Vector< size_t > & allIds,
    size_t anonId,
    size_t id);
  bool processRedesc(Vector< Person > & persons, Vector< size_t > & allIds, size_t id, const std::string & description);

}
#endif
