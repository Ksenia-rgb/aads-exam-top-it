#include <iostream>
#include <string>
#include <fstream>
#include "list.hpp"
#include "person.hpp"

namespace khalikov {
  void output(List< khalikov::Person > *h, std::ostream &out)
  {
    List< khalikov::Person > *curr = h;
    while (curr)
    {
      out << curr->val.id << ' ' << curr->val.info << '\n';
      curr = curr->next;
    }
  }
}

int main(int argc, char **argv)
{
  if (argc != 3) {
    return 1;
  }

  std::ifstream input(argv[1]);
  if (!input.is_open()) {
    return 2;
  }
  std::ofstream out(argv[2]);
  if (!out.is_open()) {
    return 2;
  }

  khalikov::List< khalikov::Person > *h = nullptr;
  std::string line;
  while (input.peek() != EOF) {
    khalikov::getPerson(input, h);
  }
  khalikov::output(h, out);
  khalikov::clear(h);
}
