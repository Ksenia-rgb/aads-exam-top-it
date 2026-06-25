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

const studilova::Person *studilova::findPersonById(
  const PersonArray &array,
  std::size_t id
)
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

void studilova::appendAnon(PersonArray &array, std::size_t id)
{
  if (!containsPersonId(array, id))
  {
    Person person;
    person.id_ = id;
    person.info_ = "";
    appendPerson(array, person);
  }
}
