#include "meet.hpp"

namespace
{
  size_t getNextCapacity(size_t capacity)
  {
    if (capacity == 0)
    {
      return 4;
    }

    return capacity * 2;
  }

  void reserveMeetArray(studilova::MeetArray &array, size_t newCapacity)
  {
    if (newCapacity <= array.capacity_)
    {
      return;
    }

    studilova::Meet* newData = new studilova::Meet[newCapacity];

    for (size_t i = 0; i < array.size_; ++i)
    {
      newData[i] = array.data_[i];
    }

    delete[] array.data_;

    array.data_ = newData;
    array.capacity_ = newCapacity;
  }
}

void studilova::initMeetArray(MeetArray &array)
{
  array.data_ = nullptr;
  array.size_ = 0;
  array.capacity_ = 0;
}

void studilova::destroyMeetArray(MeetArray &array)
{
  delete[] array.data_;
  array.data_ = nullptr;
  array.size_ = 0;
  array.capacity_ = 0;
}

void studilova::appendMeet(MeetArray &array, const Meet &meet)
{
  if (array.size_ == array.capacity_)
  {
    reserveMeetArray(array, getNextCapacity(array.capacity_));
  }

  array.data_[array.size_] = meet;
  ++array.size_;
}
