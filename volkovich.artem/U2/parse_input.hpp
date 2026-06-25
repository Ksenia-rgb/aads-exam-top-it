#include "../common/list.hpp"
#include <fstream>
#include "sstream"


volkovich::List<volkovich::Meet>* getMeets(std::ifstream& f) {
  volkovich::List<volkovich::Meet> mt;
  std::string line;
  while (std::getline(f, line)) {
    size_t who, with_who, length;
    std::stringstream ss(line);
    if (!(ss>>who>>with_who>>length)) {
      return nullptr;
    }
    volkovich::Meet(who, with_who, length);
  }
  return &mt;
}
