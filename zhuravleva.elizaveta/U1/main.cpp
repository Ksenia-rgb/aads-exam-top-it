#include "person.hpp"

int main()
{
  zhuravleva::DynamicArray< zhuravleva::Person > persons;
  zhuravleva::init(persons);
  zhuravleva::destroy(persons);
  return 0;
}
