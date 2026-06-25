#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <cstddef>
namespace kitserov
{
  struct Person
  {
    size_t id_;
    std::string info_;
  };
  struct PersonsContainer
  {
    Person* data_;
    size_t size_;
    size_t capacity_;
  };
  template< class Container >
  void destroy(Container storage)
  {
    delete[] storage.data_;
    storage.data_ = nullptr;
    storage.size_ = 0;
    storage.capacity_ = 0;
  }
  bool contains(const PersonsContainer& container, size_t id)
  {
    for (size_t i = 0; i < container.size_; ++i) {
      if (container.data_[i].id_ == id) {
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
    if (container.size_ == container.capacity_) {
      size_t new_cap = (container.capacity_ == 0) ? 8 : container.capacity_ * 2;
      Person* new_data = new Person[new_cap];
      try {
        for (size_t i = 0; i < container.size_; ++i) {
          new_data[i] = container.data_[i];
        }
        new_data[container.size_] = Person{id, info};
      } catch (...) {
        delete[] new_data;
        throw; 
      }
      delete[] container.data_;
      container.data_ = new_data;
      container.capacity_ = new_cap;
    } else {
      container.data_[container.size_] = Person{id, info};
    }
    container.size_++;
    return true;
  }
}

#endif