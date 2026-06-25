#include "vector.hpp"
#include <stdexcept>

namespace madieva {

  PersonArray createPersonArray() {
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
      if (new_capacity < arr.capacity_) {
        throw std::length_error("capacity overflow");
      }
      Person * new_data = new Person[new_capacity];
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

  Person & at(PersonArray & arr, size_t index) {
    return arr.data_[index];
  }

  const Person & at(const PersonArray & arr, size_t index) {
    return arr.data_[index];
  }

  size_t findById(const PersonArray & arr, size_t id) {
    for (size_t i = 0; i < arr.size_; ++i) {
      if (arr.data_[i].id_ == id) {
        return i;
      }
    }
    return static_cast< size_t >(-1);
  }

  void removeAt(PersonArray & arr, size_t index) {
    if (index >= arr.size_) {
      return;
    }
    for (size_t i = index; i + 1 < arr.size_; ++i) {
      arr.data_[i] = arr.data_[i + 1];
    }
    --arr.size_;
  }

  MeetArray createMeetArray() {
    MeetArray arr;
    arr.data_ = nullptr;
    arr.size_ = 0;
    arr.capacity_ = 0;
    return arr;
  }

  void destroyArray(MeetArray & arr) noexcept {
    delete[] arr.data_;
    arr.data_ = nullptr;
    arr.size_ = 0;
    arr.capacity_ = 0;
  }

  void pushBack(MeetArray & arr, const Meet & meet) {
    if (arr.size_ == arr.capacity_) {
      size_t new_capacity = (arr.capacity_ == 0) ? 1 : arr.capacity_ * 2;
      if (new_capacity < arr.capacity_) {
        throw std::length_error("capacity overflow");
      }
      Meet * new_data = new Meet[new_capacity];
      for (size_t i = 0; i < arr.size_; ++i) {
        new_data[i] = arr.data_[i];
      }
      delete[] arr.data_;
      arr.data_ = new_data;
      arr.capacity_ = new_capacity;
    }
    arr.data_[arr.size_] = meet;
    ++arr.size_;
  }

  size_t getSize(const MeetArray & arr) noexcept {
    return arr.size_;
  }

  Meet & at(MeetArray & arr, size_t index) {
    return arr.data_[index];
  }

  const Meet & at(const MeetArray & arr, size_t index) {
    return arr.data_[index];
  }

  void removeAt(MeetArray & arr, size_t index) {
    if (index >= arr.size_) {
      return;
    }
    for (size_t i = index; i + 1 < arr.size_; ++i) {
      arr.data_[i] = arr.data_[i + 1];
    }
    --arr.size_;
  }

}
