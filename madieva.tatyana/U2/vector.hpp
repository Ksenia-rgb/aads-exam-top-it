#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "person.hpp"
#include <cstddef>

namespace madieva {

  struct Meet {
    std::size_t person1_id_;
    std::size_t person2_id_;
    std::size_t duration_;
  };
  struct PersonArray {
    Person * data_;
    size_t size_;
    size_t capacity_;
  };

  struct MeetArray {
    Meet* data_;
    std::size_t size_;
    std::size_t capacity_;
  };

  PersonArray createArray();
  void destroyArray(PersonArray & arr) noexcept;
  void pushBack(PersonArray & arr, const Person& person);
  size_t getSize(const PersonArray & arr) noexcept;
  Person & at(PersonArray & arr, size_t index);
  const Person & at(const PersonArray & arr, size_t index);
  std::size_t findById(const PersonArray& arr, std::size_t id);
  void removeAt(PersonArray& arr, std::size_t index);

  MeetArray createMeetArray();
  void destroyArray(MeetArray& arr) noexcept;
  void pushBack(MeetArray& arr, const Meet& meet);
  std::size_t getSize(const MeetArray& arr) noexcept;
  Meet& at(MeetArray& arr, std::size_t index);
  const Meet& at(const MeetArray& arr, std::size_t index);
  void removeAt(MeetArray& arr, std::size_t index);

}

#endif
