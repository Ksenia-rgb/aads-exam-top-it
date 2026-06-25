#include "meet.hpp"
#include <iostream>

bool petrov::loadMeets(std::istream& in, MeetData& meets)
{
  size_t id1, id2, time;
  while (in >> id1 >> id2 >> time)
  {
    if (id1 == id2)
    {
      continue;
    }
    if (meets.saved_ % 8 == 0)
    {
      Meet* newData = new Meet[meets.saved_ + 8];
      for (size_t i = 0; i < meets.saved_; ++i)
      {
        newData[i] = meets.data_[i];
      }
      delete[] meets.data_;
      meets.data_ = newData;
    }
    meets.data_[meets.saved_].first->id = id1;
    meets.data_[meets.saved_].second->id = id2;
    meets.data_[meets.saved_].time = time;
    meets.saved_++;
  }

  if (in.peek() != std::char_traits< char >::eof() && in.fail())
    {
      return false;
    }
  return true;
}

void petrov::executeCommands(std::istream& in, std::ostream& out, petrov::Data& persons, MeetData& meets);
