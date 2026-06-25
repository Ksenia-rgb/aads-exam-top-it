#include <iostream>

namespace donkeev
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  struct PersonArray
  {
    std::pair< size_t, Person* > data;
    size_t size;
    size_t capacity;
  };
}
int main()
{
  
  


}