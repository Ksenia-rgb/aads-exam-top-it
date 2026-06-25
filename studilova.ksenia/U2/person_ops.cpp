#include "person_ops.hpp"

studilova::Person *studilova::findPersonById(PersonArray &array, std::size_t id)
{
  for (std::size_t i = 0; i < array.size_; ++i)
  {
    if (array.data_[i].id_ == id)
    {
      return &array.data_[i];
    }
  }

  return nullptr;
}
