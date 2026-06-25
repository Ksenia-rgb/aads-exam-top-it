#include "meet.hpp"

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
