#include "person.hpp"

int main()
{
  zhuravleva::PersonArray persons;
  zhuravleva::init(persons);
  zhuravleva::destroy(persons);

  return 0;
}
