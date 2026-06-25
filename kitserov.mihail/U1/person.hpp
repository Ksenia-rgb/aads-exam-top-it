#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <cstddef>
namespace kitserov
{
  struct Person
  {
    size_t id;
    std::string info;
  };
  struct PersonsContainer
  {
    Person* data;
    size_t size;
    size_t capacity;
  };
  bool contains(const PersonsContainer& container, size_t id)
  {
    for (size_t i = 0; i < container.size; ++i) {
      if (container.data[i].id == id) {
        return true;
      }
    }
    return false;
  }
  bool addPerson(PersonsContainer& container, size_t id, const std::string& info)
  {
    if (contains(container, id)) {
      return false;
    }
    if (container.size == container.capacity) {
      size_t new_cap = (container.capacity == 0) ? 8 : container.capacity * 2;
      Person* new_data = new Person[new_cap];
      try {
        for (size_t i = 0; i < container.size; ++i) {
          new_data[i] = container.data[i];
        }
        new_data[container.size] = Person{id, info};
      } catch (...) {
        delete[] new_data;
        throw; 
      }
      delete[] container.data;
      container.data = new_data;
      container.capacity = new_cap;
    } else {
      container.data[container.size] = Person{id, info};
    }
    container.size++;
    return true;
  }
}

#endif