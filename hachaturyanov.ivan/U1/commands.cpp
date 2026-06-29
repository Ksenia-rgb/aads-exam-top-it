#include "commands.hpp"

#include <functional>
#include "data.hpp"

namespace hachaturyanov
{
  std::pair< List< size_t >, Data > readData(std::istream &in, PersonTable &persons)
  {
    std::string line = "";
    List< size_t > ids;
    Data data;
    while(getline(in, line)) {
      bool success = false;
      List< std::string > strs = split(line);
      if (strs.size() == 2) {
        if (isdigit(*(strs.begin()))) {
          std::pair< std::string, std::string > pair = splitInTwo(line);
          if (!persons.has(std::stoull(pair.first))) {
            persons.add(std::stoull(pair.first), pair.second);
            ids.addEnd(std::stoull(pair.first));
            success = true;
            data.success++;
          }
        }
      }
      if (!success) {
        data.ignored++;
      }
    }
    return { ids, data };
  }

  void printData(std::ostream &out, PersonTable &persons, List< size_t > order)
  {
    auto it = order.begin();
    do {
      out << *it << ' ' << persons[*it] << '\n';
      ++it;
    } while (it != order.begin());
  }
}
