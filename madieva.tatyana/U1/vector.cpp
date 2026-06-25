#include "vector.hpp"

namespace madieva {

  PersonArray createArray() {
    PersonArray arr;
    arr.data_ = nullptr;
    arr.size_ = 0;
    arr.capacity_ = 0;
    return arr;
  }

  void destroyArray(PersonArray & arr) noexcept {
    delete[] arr.data_;
    arr.data_ = nullptr;
    arr.size_ = 0;
    arr.capacity_ = 0;
  }

  void pushBack(PersonArray & arr, const Person & person) {
    if (arr.size_ == arr.capacity_) {
      size_t new_capacity = (arr.capacity_ == 0) ? 1 : arr.capacity_ * 2;
      Person* new_data = new Person[new_capacity];

      for (size_t i = 0; i < arr.size_; ++i) {
        new_data[i] = arr.data_[i];
      }

      delete[] arr.data_;
      arr.data_ = new_data;
      arr.capacity_ = new_capacity;
    }

    arr.data_[arr.size_] = person;
    ++arr.size_;
  }

  size_t getSize(const PersonArray & arr) noexcept {
    return arr.size_;
  }

  Person & at(PersonArray& arr, size_t index) {
    return arr.data_[index];
  }

  const Person & at(const PersonArray & arr, size_t index) {
    return arr.data_[index];
  }
}
