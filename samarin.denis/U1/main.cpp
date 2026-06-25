#include <iostream>

#include "person.hpp"

int main()
{
  samarin::Person person{ 0, "" };
  static_cast< void >(person);
  return 0;
}
