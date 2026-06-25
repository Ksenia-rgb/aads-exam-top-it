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
  template< class Container >
  bool contains(const Container& container, size_t id)
  {
    for (size_t i = 0; i < container.size_; ++i) {
      if (container.data_[i].id_ == id) {
        return true;
      }
    }
    return false;
  }
  size_t findIndex(const PersonsContainer& c, size_t id)
  {
    for (size_t i = 0; i < c.size_; ++i) {
      if (c.data_[i].id_ == id) {
        return i; 
      }
    }
    return c.size_;
  }
  template< class T, class Container >
  bool add(Container& container, size_t id, const std::string& info)
  {
    if (contains(container, id)) {
      return false;
    }
    if (info.find_first_not_of(" \t") == std::string::npos) {
      return false;
    }
    if (container.size_ == container.capacity_) {
      size_t new_cap = (container.capacity_ == 0) ? 8 : container.capacity_ * 2;
      T* new_data = new T[new_cap];
      try {
        for (size_t i = 0; i < container.size_; ++i) {
          new_data[i] = container.data_[i];
        }
        new_data[container.size_] = T{id, info};
      } catch (...) {
        delete[] new_data;
        throw; 
      }
      delete[] container.data_;
      container.data_ = new_data;
      container.capacity_ = new_cap;
    } else {
      container.data_[container.size_] = T{id, info};
    }
    container.size_++;
    return true;
  }
  template< class Container >
  bool remove(Container& c, size_t id)
  {
    for (size_t i = 0; i < c.size_; ++i) {
      if (c.data_[i] == id) {
        for (size_t j = i; j < c.size_ - 1; ++j) {
          c.data_[j] = c.data_[j + 1];
        }
        --c.size_;
        return true;
      }
    }
    return false;
  }
  bool updatePerson(PersonsContainer& c, std::size_t id, const std::string& newDesc) {
    int idx = findIndex(c, id);
    if (idx == -1) {
      return false;
    }
    if (newDesc.find_first_not_of(" \t") == std::string::npos) {
      return false;
    }
    c.data_[idx].info_ = newDesc;
    return true;
  }

}

#endif