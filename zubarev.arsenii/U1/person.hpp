#include <iostream>
namespace zubarev
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  struct PersonArray
  {
    Person* data;
    size_t size;
    size_t capacity;
  };

  struct HashSet
{
  size_t* data;
  bool* used;
  size_t capacity;
};

}
