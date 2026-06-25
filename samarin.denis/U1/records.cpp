#include "records.hpp"

#include <cstddef>
#include <istream>
#include <ostream>
#include <string>

#include "parsing.hpp"

namespace {
  using PersonNode = samarin::detail::list_node_t< samarin::Person >;

  bool containsId(const samarin::detail::list_t< samarin::Person > & records, std::size_t id)
  {
    const auto hasId = [id](const samarin::Person & person)
    {
      return person.id == id;
    };
    return samarin::detail::findValue(records, hasId) != nullptr;
  }
}

samarin::counts_t samarin::readRecords(std::istream & input, detail::list_t< Person > & records)
{
  counts_t counts{ 0, 0 };
  std::string line;
  while (std::getline(input, line)) {
    Person person{ 0, "" };
    if (!detail::parseRecord(line, person.id, person.info) || containsId(records, person.id)) {
      ++counts.ignored;
    } else {
      detail::pushBack(records, person);
      ++counts.accepted;
    }
  }
  return counts;
}

void samarin::writeRecords(std::ostream & output, const detail::list_t< Person > & records)
{
  for (const PersonNode * node = records.head; node != nullptr; node = node->next) {
    output << node->value.id << ' ' << node->value.info << '\n';
  }
}
