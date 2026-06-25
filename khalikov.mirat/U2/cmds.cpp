#include <iostream>

namespace khalikov {

  void anons(std::ostream &out, std::istream &, khalikov::Data &d) {
    size_t count = 0;
    khalikov::List<khalikov::Person> *curr = d.persons;
    while (curr) {
      if (curr->val.info.empty()) count++;
      curr = curr->next;
    }
    if (count == 0) {
      out << "<EMPTY>\n";
      return;
    }
    khalikov::Person* arr = new khalikov::Person[count];
    size_t i = 0;
    curr = d.persons;
    while (curr) {
      if (curr->val.info.empty()) {
        arr[i++] = curr->val;
      }
      curr = curr->next;
    }
    std::sort(arr, arr + count, [](const khalikov::Person &a, const khalikov::Person &b) {
      return a.id < b.id;
    });
    for (size_t j = 0; j < count; ++j) {
      out << arr[j].id << "\n";
    }
    delete[] arr;
  }
}
