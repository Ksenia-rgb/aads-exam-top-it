#include "meet.hpp"

namespace hachaturyanov
{
  Meet::Meet(List< List< std::string > > data):
   meets(),
   people()
  {
    auto it = data.begin();
    do {
      List< std::string > line = *it;
      auto newit = line.begin();
      std::string person1 = *newit;
      if (!people.has(person1)) {
        if (people.size() * 2 / people.capacity() > 1) {
          people.rehash(people.capacity() * 2);
        }
        people.add(std::stoull(person1), "");
      }
      ++newit;
      std::string person2 = *newit;
      if (!people.has(person2)) {
        if (people.size() * 2 / people.capacity() > 1) {
          people.rehash(people.capacity() * 2);
        }
        people.add(std::stoull(person2), "");
      }
      ++newit;
      if (person1 != person2) {
        if (meets.size() * 2 / meets.size() > 1) {
          meets.rehash(meets.capacity() * 2);
        }
        meets.add({ person1, person2 }, std::stoull(*newit));
      }
      ++it;
    } while (it != data.begin());
  }

  List< size_t > Meet::getAnons() const
  {
    List< size_t > result;
    List< size_t > allpeople = people.keys();
    for (size_t i = 0; i < people.size(); i++) {
      auto it = allpeople.begin();
      do {
        if (people[*it] == "") {
          result.insertSorted(*it);
        }
        ++it;
      } while (it != allpeople.begin());
    }
    return result;
  }
}