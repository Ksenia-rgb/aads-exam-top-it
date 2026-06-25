#include <iostream>

namespace donkeev
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  struct PersonNode
  {
    std::pair< size_t, Person* > data_;
    PersonTree* neext_;
    PersonTree* prev_;
  };
  struct PersonTree
  {
    PersonNode* head_;
    PersonNode* tail_;
    size_t size;
  };
}
int main()
{
  
  


}