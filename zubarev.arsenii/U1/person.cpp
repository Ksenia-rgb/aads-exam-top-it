#include "person.hpp"
void zubarev::init(PersonArray& arr)
{
  arr.data = nullptr;
  arr.size = 0;
  arr.capacity = 0;
}
void zubarev::destroy(PersonArray& arr)
{
  delete[] arr.data;
}
void zubarev::resize(PersonArray& arr)
{}
void zubarev::push(PersonArray& arr, const Person& value)
{}

void zubarev::init(HashSet& set)
{}
void zubarev::destroy(HashSet& set)
{}
size_t zubarev::hash(const HashSet& set, size_t value)
{}
bool zubarev::contains(const HashSet& set, size_t value)
{}
void zubarev::insert(HashSet& set, size_t value)
{}
