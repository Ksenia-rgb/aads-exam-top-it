#ifndef CONTEXT_HPP
#define CONTEXT_HPP
#include "../U1/person.hpp"

namespace strelnikov
{
  struct Meeting
  {
    size_t id1;
    size_t id2;
    size_t duration;
  };

  template < typename T > struct DynArray
  {
    T *data;
    size_t size;
    size_t capacity;
  };

  struct Context
  {
    DynArray< Person > persons;
    DynArray< Meeting > meetings;
  };

  template < typename T > void dynarray_init(DynArray< T > &arr, size_t cap)
  {
    arr.data = new T[cap];
    arr.size = 0;
    arr.capacity = cap;
  }

  template < typename T > void dynarray_push(DynArray< T > &arr, const T &val)
  {
    if (arr.size == arr.capacity) {
      size_t new_cap = arr.capacity == 0 ? 4 : arr.capacity * 2;
      T *new_data = new T[new_cap];
      for (size_t i = 0; i < arr.size; ++i) {
        new_data[i] = arr.data[i];
      }
      delete[] arr.data;
      arr.data = new_data;
      arr.capacity = new_cap;
    }
    arr.data[arr.size++] = val;
  }

  template < typename T > void dynarray_destroy(DynArray< T > &arr)
  {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
  }

  void ensure_person(Context &ctx, size_t id)
  {
    for (size_t i = 0; i < ctx.persons.size; ++i) {
      if (ctx.persons.data[i].id == id) {
        return;
      }
    }

    Person p{id, ""};
    dynarray_push(ctx.persons, p);
  }
}

#endif
