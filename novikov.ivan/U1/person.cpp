#include "person.hpp"

void novikov::drop(PersonArray& arr)
{
  delete[] arr.data;
}

void novikov::expand(PersonArray& arr)
{
  size_t new_cap = arr.capacity == 0 ? 8 : arr.capacity * 2;
  Person* new_data = new Person[new_cap];

  for (size_t i = 0; i < arr.size; ++i) {
    new_data[i] = std::move(arr.data[i]);
  }
  delete[] arr.data;

  arr.data = new_data;
  arr.capacity = new_cap;
}

void novikov::push(PersonArray& arr, const Person& value)
{
  if (arr.size == arr.capacity) {
    expand(arr);
  }
  arr.data[arr.size] = value;
  ++arr.size;
}

void novikov::drop(IdSet& set)
{
  delete[] set.data;
  delete[] set.used;
}

size_t novikov::hash(const IdSet& set, size_t value)
{
  return value % set.capacity;
}

bool novikov::contains(const IdSet& set, size_t value)
{
  size_t pos = hash(set, value);

  for (size_t i = 0; i < set.capacity; ++i) {
    size_t cur = (pos + i) % set.capacity;
    if (!set.used[cur]) {
      return false;
    }
    if (set.data[cur] == value) {
      return true;
    }
  }
  return false;
}

void novikov::insert(IdSet& set, size_t value)
{
  size_t pos = hash(set, value);

  for (size_t i = 0; i < set.capacity; ++i) {
    size_t cur = (pos + i) % set.capacity;
    if (!set.used[cur]) {
      set.data[cur] = value;
      set.used[cur] = true;
      return;
    }
  }
}
